#include "audioplayer.h"

#include <algorithm>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusInterface>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusReply>
#include <QDBusVariant>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QLoggingCategory>
#include <QMap>
#include <QMediaMetaData>
#include <QRegularExpression>
#include <QSet>
#include <QUrl>

Q_LOGGING_CATEGORY(mediaPlayer, "app.mediaPlayer")

using BluezInterfaceMap = QMap<QString, QVariantMap>;
using BluezManagedObjects = QMap<QDBusObjectPath, BluezInterfaceMap>;
Q_DECLARE_METATYPE(BluezInterfaceMap)
Q_DECLARE_METATYPE(BluezManagedObjects)

namespace {
constexpr auto kBluezService = "org.bluez";
constexpr auto kObjectManagerInterface = "org.freedesktop.DBus.ObjectManager";
constexpr auto kAdapterInterface = "org.bluez.Adapter1";
constexpr auto kDeviceInterface = "org.bluez.Device1";
constexpr auto kMediaPlayerInterface = "org.bluez.MediaPlayer1";
constexpr auto kMediaControlInterface = "org.bluez.MediaControl1";

QString dbusObjectPathString(const QVariant &value)
{
    QVariant unwrapped = value;
    if (value.metaType() == QMetaType::fromType<QDBusVariant>())
        unwrapped = value.value<QDBusVariant>().variant();

    if (unwrapped.canConvert<QDBusObjectPath>())
        return unwrapped.value<QDBusObjectPath>().path();
    return unwrapped.toString();
}

QVariant unwrapDbusVariant(const QVariant &value)
{
    if (value.metaType() == QMetaType::fromType<QDBusVariant>())
        return value.value<QDBusVariant>().variant();
    return value;
}

QVariantMap dbusVariantMap(const QVariant &value)
{
    const QVariant unwrapped = unwrapDbusVariant(value);
    if (unwrapped.metaType() == QMetaType::fromType<QDBusArgument>())
        return qdbus_cast<QVariantMap>(unwrapped.value<QDBusArgument>());
    return unwrapped.toMap();
}

QString dbusString(const QVariant &value)
{
    return unwrapDbusVariant(value).toString().trimmed();
}

bool dbusBool(const QVariant &value)
{
    return unwrapDbusVariant(value).toBool();
}

int dbusInt(const QVariant &value, int fallback = 0)
{
    const QVariant unwrapped = unwrapDbusVariant(value);
    bool ok = false;
    const int result = unwrapped.toInt(&ok);
    return ok ? result : fallback;
}

QStringList dbusStringList(const QVariant &value)
{
    const QVariant unwrapped = unwrapDbusVariant(value);
    if (unwrapped.metaType() == QMetaType::fromType<QDBusArgument>())
        return qdbus_cast<QStringList>(unwrapped.value<QDBusArgument>());
    return unwrapped.toStringList();
}

bool isBluetoothAudioDevice(const QVariantMap &properties)
{
    // BlueZ publishes the supported profiles as 128-bit UUID strings. These
    // short UUID fragments cover A2DP and AVRCP roles used by phone audio.
    static const QStringList audioProfileUuids = {
        QStringLiteral("0000110a"), // Audio Source
        QStringLiteral("0000110b"), // Audio Sink
        QStringLiteral("0000110c"), // A/V Remote Control Target
        QStringLiteral("0000110d"), // Advanced Audio Distribution
        QStringLiteral("0000110e"), // A/V Remote Control
        QStringLiteral("0000110f")  // A/V Remote Control Controller
    };

    const QStringList uuids = dbusStringList(properties.value(QStringLiteral("UUIDs")));
    for (const QString &uuid : uuids) {
        const QString normalized = uuid.toLower();
        for (const QString &audioUuid : audioProfileUuids) {
            if (normalized.contains(audioUuid))
                return true;
        }
    }
    return false;
}

QString bluetoothDeviceName(const QVariantMap &properties)
{
    static const QRegularExpression macAddressPattern(
                QStringLiteral("^(?:[0-9A-Fa-f]{2}[:-]){5}[0-9A-Fa-f]{2}$"));

    const QString alias = dbusString(
                properties.value(QStringLiteral("Alias")));
    const QString remoteName = dbusString(
                properties.value(QStringLiteral("Name")));

    QString name;
    if (!alias.isEmpty() && !macAddressPattern.match(alias).hasMatch())
        name = alias;
    else if (!remoteName.isEmpty()
             && !macAddressPattern.match(remoteName).hasMatch())
        name = remoteName;

    // Never expose the hardware address as the user-facing device name. BlueZ
    // may publish Alias/Name a little later during discovery; the refresh loop
    // will replace this temporary label as soon as the real name arrives.
    return name.isEmpty()
            ? QStringLiteral("Detecting device name...")
            : name;
}

QString mediaPlayerDevicePath(const QString &playerPath,
                              const QVariantMap &properties)
{
    QString devicePath = dbusObjectPathString(
                properties.value(QStringLiteral("Device")));

    // Some BlueZ versions omit MediaPlayer1.Device from managed-object
    // snapshots. The player object is still nested below its Device1 path.
    if (devicePath.isEmpty()) {
        const qsizetype playerSegment = playerPath.indexOf(QStringLiteral("/player"));
        if (playerSegment > 0)
            devicePath = playerPath.left(playerSegment);
    }
    return devicePath;
}

qint64 variantToInt64(const QVariant &value)
{
    const QVariant unwrapped = unwrapDbusVariant(value);
    bool ok = false;
    const qulonglong result = unwrapped.toULongLong(&ok);
    return ok ? static_cast<qint64>(result) : 0;
}
}

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent),
      m_mediaPlayer(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this))
{
    qDBusRegisterMetaType<BluezInterfaceMap>();
    qDBusRegisterMetaType<BluezManagedObjects>();

    m_mediaPlayer->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.5f);

    // Keep Bluetooth/AVRCP state in sync with BlueZ while the source is active.
    m_bluetoothRefreshTimer.setInterval(1200);
    connect(&m_bluetoothRefreshTimer, &QTimer::timeout, this, [this]() {
        syncBluetoothState(false);
    });

    // Forward Qt Multimedia signals through the wrapper's public signals.
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged,
            this, &AudioPlayer::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged,
            this, &AudioPlayer::durationChanged);
    connect(m_mediaPlayer, &QMediaPlayer::playingChanged,
            this, &AudioPlayer::playingStateChanged);
    connect(m_audioOutput, &QAudioOutput::mutedChanged,
            this, &AudioPlayer::muteStateChanged);
    connect(m_audioOutput, &QAudioOutput::volumeChanged,
            this, &AudioPlayer::volumeChanged);

    // Playback errors.
    connect(m_mediaPlayer, &QMediaPlayer::errorOccurred, this,
            [this](QMediaPlayer::Error error, const QString &errorText) {
        if (error == QMediaPlayer::NoError)
            return;

        // If a USB drive disappears while a track is playing, reflect that
        // immediately in the QML USB state instead of leaving USB CONNECTED.
        if (m_isUsbMode
                && !m_usbRootPath.isEmpty()
                && !QDir(m_usbRootPath).exists()) {
            clearUsb();
            setPlaybackError(QStringLiteral("USB media is no longer available"));
            return;
        }

        const QString message = errorText.isEmpty()
                ? m_mediaPlayer->errorString()
                : errorText;
        setPlaybackError(message);
    });

    // Metadata belongs to the currently loaded local, radio, or USB source.
    connect(m_mediaPlayer, &QMediaPlayer::metaDataChanged, this, [this]() {
        if (m_isBluetoothMode)
            return;

        const QMediaMetaData metaData = m_mediaPlayer->metaData();

        m_audioTitle = metaData.stringValue(QMediaMetaData::Title);
        m_audioAuthor = metaData.stringValue(QMediaMetaData::ContributingArtist);
        m_audioAlbum = metaData.stringValue(QMediaMetaData::AlbumTitle);
        m_audioType = metaData.stringValue(QMediaMetaData::Genre);

        // Local and USB files may not contain an embedded title tag.
        // In that case, use the current filename as the display title.
        if (!m_isRadioMode && m_audioTitle.isEmpty()) {
            QString currentFilePath;

            if (m_isUsbMode
                    && m_currentUsbTrackIndex >= 0
                    && m_currentUsbTrackIndex < m_usbTracks.size()) {
                currentFilePath = m_usbTracks.at(m_currentUsbTrackIndex);
            } else if (m_currentPlaylistIndex >= 0
                       && m_currentPlaylistIndex < m_playlist.size()) {
                currentFilePath = m_playlist.at(m_currentPlaylistIndex);
            }

            if (!currentFilePath.isEmpty())
                m_audioTitle = QFileInfo(currentFilePath).completeBaseName();
        }

        emit metaDataChanged();

        qCDebug(mediaPlayer) << "Title:" << m_audioTitle
                             << "Author:" << m_audioAuthor
                             << "Album:" << m_audioAlbum
                             << "Genre:" << m_audioType;
    });

    // End-of-file advances the active local/USB playlist.
    // Radio statuses drive the radioReconnecting API.
    connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this,
            [this](QMediaPlayer::MediaStatus status) {
        if (m_isRadioMode) {
            const bool reconnecting = status == QMediaPlayer::LoadingMedia
                    || status == QMediaPlayer::BufferingMedia
                    || status == QMediaPlayer::StalledMedia;
            setRadioReconnecting(reconnecting);
        } else {
            setRadioReconnecting(false);
        }

        if (status == QMediaPlayer::EndOfMedia)
            next();
    });

    // Same initial radio catalog as the Qt6_QML reference project.
    m_radioStations = {
        QVariantMap{{"name", "Quran Radio Cairo"},
                    {"country", "🇪🇬 Egypt"},
                    {"url", "http://n12.radiojar.com/8s5u5tpdtwzuv"}},
        QVariantMap{{"name", "Saudi Quran Radio"},
                    {"country", "🇸🇦 Saudi Arabia"},
                    {"url", "http://live.mp3quran.net:8008/"}},
        QVariantMap{{"name", "Quran Radio Nablus"},
                    {"country", "🇵🇸 Palestine"},
                    {"url", "http://www.quran-radio.org:8002/"}},
        QVariantMap{{"name", "Quran Radio"},
                    {"country", "🇸🇦 Saudi Arabia"},
                    {"url", "http://live.mp3quran.net:8002/"}}
    };
}

// ============================================================
// Getters: core playback
// ============================================================

bool AudioPlayer::getPlayingState() const
{
    return m_isBluetoothMode ? m_bluetoothPlaying : m_mediaPlayer->isPlaying();
}

qint64 AudioPlayer::getPosition() const
{
    return m_isBluetoothMode ? m_bluetoothPosition : m_mediaPlayer->position();
}

qint64 AudioPlayer::getDuration() const
{
    return m_isBluetoothMode ? m_bluetoothDuration : m_mediaPlayer->duration();
}

// ============================================================
// Getters: audio output
// ============================================================

bool AudioPlayer::getMuteState() const
{
    return m_audioOutput->isMuted();
}

float AudioPlayer::getVolume() const
{
    return m_audioOutput->volume();
}

// ============================================================
// Getters: local source
// ============================================================

QStringList AudioPlayer::getPlaylist() const
{
    return m_playlist;
}

int AudioPlayer::getCurrentPlaylistIndex() const
{
    return m_currentPlaylistIndex;
}

// ============================================================
// Getters: radio source
// ============================================================

bool AudioPlayer::getRadioMode() const
{
    return m_isRadioMode;
}

QVariantList AudioPlayer::getRadioStations() const
{
    return m_radioStations;
}

QString AudioPlayer::getCurrentRadioStationName() const
{
    return m_currentStationName;
}

QString AudioPlayer::getCurrentStationCountry() const
{
    return m_currentRadioStationCountry;
}

bool AudioPlayer::getRadioReconnectingState() const
{
    return m_radioReconnecting;
}

// ============================================================
// Getters: USB source
// ============================================================

bool AudioPlayer::getUsbMode() const
{
    return m_isUsbMode;
}

bool AudioPlayer::getUsbConnected() const
{
    return m_usbConnected;
}

QString AudioPlayer::getUsbRootPath() const
{
    return m_usbRootPath;
}

QStringList AudioPlayer::getUsbTracks() const
{
    return m_usbTracks;
}

int AudioPlayer::getCurrentUsbTrackIndex() const
{
    return m_currentUsbTrackIndex;
}

// ============================================================
// Getters: Bluetooth source
// ============================================================

bool AudioPlayer::getBluetoothMode() const
{
    return m_isBluetoothMode;
}

bool AudioPlayer::getBluetoothAvailable() const
{
    return m_bluetoothAvailable;
}

bool AudioPlayer::getBluetoothScanning() const
{
    return m_bluetoothScanning;
}

bool AudioPlayer::getBluetoothConnected() const
{
    return m_bluetoothConnected;
}

QVariantList AudioPlayer::getBluetoothDevices() const
{
    return m_bluetoothDevices;
}

QString AudioPlayer::getBluetoothDeviceName() const
{
    return m_bluetoothDeviceName;
}

QString AudioPlayer::getBluetoothDeviceAddress() const
{
    return m_bluetoothDeviceAddress;
}

QString AudioPlayer::getBluetoothPlaybackStatus() const
{
    return m_bluetoothPlaybackStatus;
}

bool AudioPlayer::getBluetoothMediaControlsAvailable() const
{
    return !m_bluetoothMediaPlayerPath.isEmpty()
            || !m_bluetoothMediaControlPath.isEmpty();
}

// ============================================================
// Getters: metadata / error
// ============================================================

QString AudioPlayer::getAudioTitle() const
{
    return m_audioTitle;
}

QString AudioPlayer::getAudioAuthor() const
{
    return m_audioAuthor;
}

QString AudioPlayer::getAudioAlbum() const
{
    return m_audioAlbum;
}

QString AudioPlayer::getAudioType() const
{
    return m_audioType;
}

QString AudioPlayer::getErrorString() const
{
    return m_errorString;
}

// ============================================================
// Setters: core / audio output
// ============================================================

void AudioPlayer::setPosition(qint64 position_ms)
{
    if (m_isBluetoothMode) {
        // BlueZ MediaPlayer1 exposes Position as read-only.
        return;
    }

    if (position_ms < 0)
        return;

    // duration can be zero while a stream/file is still being loaded.
    if (getDuration() > 0 && position_ms > getDuration()) {
        qCWarning(mediaPlayer) << "Invalid position:" << position_ms
                               << "duration:" << getDuration();
        return;
    }

    m_mediaPlayer->setPosition(position_ms);
}

void AudioPlayer::setMuteState(bool mute_state)
{
    m_audioOutput->setMuted(mute_state);
}

void AudioPlayer::setVolume(float volume_level)
{
    m_audioOutput->setVolume(qBound(0.0f, volume_level, 1.0f));
}

// ============================================================
// Setters: USB source state
// ============================================================

void AudioPlayer::setUsbMode(bool usb_mode)
{
    if (m_isUsbMode == usb_mode)
        return;

    m_isUsbMode = usb_mode;
    emit usbModeChanged();
}

void AudioPlayer::setUsbConnected(bool connected)
{
    if (m_usbConnected == connected)
        return;

    m_usbConnected = connected;
    emit usbConnectedChanged();
}

void AudioPlayer::setUsbRootPath(const QString &usb_root_path)
{
    if (m_usbRootPath == usb_root_path)
        return;

    m_usbRootPath = usb_root_path;
    emit usbRootPathChanged();
}

void AudioPlayer::setUsbTracks(const QStringList &usb_tracks)
{
    if (m_usbTracks == usb_tracks)
        return;

    m_usbTracks = usb_tracks;
    emit usbTracksChanged();
}

void AudioPlayer::setCurrentUsbTrackIndex(int usb_track_index)
{
    if (m_currentUsbTrackIndex == usb_track_index)
        return;

    m_currentUsbTrackIndex = usb_track_index;
    emit currentUsbTrackIndexChanged();
}

// ============================================================
// Common playback controls
// ============================================================

void AudioPlayer::playPause()
{
    if (m_isBluetoothMode) {
        sendBluetoothMediaCommand(m_bluetoothPlaying
                                  ? QStringLiteral("Pause")
                                  : QStringLiteral("Play"));
        return;
    }

    if (getPlayingState())
        m_mediaPlayer->pause();
    else
        m_mediaPlayer->play();
}

void AudioPlayer::stop()
{
    if (m_isBluetoothMode) {
        sendBluetoothMediaCommand(QStringLiteral("Stop"));
        return;
    }

    m_mediaPlayer->stop();
}

void AudioPlayer::next()
{
    if (m_isBluetoothMode) {
        sendBluetoothMediaCommand(QStringLiteral("Next"));
        return;
    }

    if (m_isRadioMode) {
        nextRadio();
        return;
    }

    if (m_isUsbMode) {
        if (m_usbTracks.isEmpty()) {
            setPlaybackError(QStringLiteral("USB playlist is empty"));
            return;
        }

        const int nextUsbIndex =
                (m_currentUsbTrackIndex + 1) % m_usbTracks.size();
        playUsbTrack(nextUsbIndex);
        return;
    }

    if (m_playlist.isEmpty()) {
        setPlaybackError(QStringLiteral("PlayList is Empty"));
        return;
    }

    m_currentPlaylistIndex = (m_currentPlaylistIndex + 1) % m_playlist.size();
    emit CurrentPlaylistIndexChanged();

    setSource(m_playlist.at(m_currentPlaylistIndex));
    m_mediaPlayer->play();

    qCInfo(mediaPlayer) << "Playing local file:"
                        << m_playlist.at(m_currentPlaylistIndex);
}

void AudioPlayer::previous()
{
    if (m_isBluetoothMode) {
        sendBluetoothMediaCommand(QStringLiteral("Previous"));
        return;
    }

    if (m_isRadioMode) {
        previousRadio();
        return;
    }

    if (m_isUsbMode) {
        if (m_usbTracks.isEmpty()) {
            setPlaybackError(QStringLiteral("USB playlist is empty"));
            return;
        }

        const int previousUsbIndex =
                (m_currentUsbTrackIndex - 1 + m_usbTracks.size())
                % m_usbTracks.size();
        playUsbTrack(previousUsbIndex);
        return;
    }

    if (m_playlist.isEmpty()) {
        setPlaybackError(QStringLiteral("PlayList is Empty"));
        return;
    }

    m_currentPlaylistIndex =
            (m_currentPlaylistIndex - 1 + m_playlist.size()) % m_playlist.size();
    emit CurrentPlaylistIndexChanged();

    setSource(m_playlist.at(m_currentPlaylistIndex));
    m_mediaPlayer->play();

    qCInfo(mediaPlayer) << "Playing local file:"
                        << m_playlist.at(m_currentPlaylistIndex);
}

// ============================================================
// Local source
// ============================================================

void AudioPlayer::loadFolder(const QString &folder_path)
{
    setBluetoothMode(false);
    const bool wasRadio = m_isRadioMode;
    m_isRadioMode = false;
    setUsbMode(false);

    m_currentStationIndex = -1;
    m_currentStationName.clear();
    m_currentRadioStationCountry.clear();
    setRadioReconnecting(false);

    if (wasRadio)
        emit radioModeChanged();
    emit currentRadioStationNameChanged();
    emit currentRadioStationCountryChanged();

    qCDebug(mediaPlayer) << "Incoming UI folder path:" << folder_path;

    const QUrl url(folder_path);
    QString localFolderPath;
    if (url.isLocalFile())
        localFolderPath = url.toLocalFile();
    else
        localFolderPath = folder_path;

    QDir dir(localFolderPath);
    if (!dir.exists()) {
        setPlaybackError(QStringLiteral("Folder does not exist: %1")
                         .arg(localFolderPath));
        return;
    }

    const QStringList filters = {
        QStringLiteral("*.mp3"),
        QStringLiteral("*.wav"),
        QStringLiteral("*.m4a"),
        QStringLiteral("*.aac"),
        QStringLiteral("*.flac"),
        QStringLiteral("*.ogg")
    };

    const QFileInfoList filteredFiles =
            dir.entryInfoList(filters, QDir::Files, QDir::Name);

    if (filteredFiles.isEmpty()) {
        setPlaybackError(QStringLiteral("No Audio Files found in: %1")
                         .arg(localFolderPath));
        return;
    }

    QStringList audioSrcPaths;
    audioSrcPaths.reserve(filteredFiles.size());
    for (const QFileInfo &file : filteredFiles)
        audioSrcPaths.append(file.absoluteFilePath());

    m_playlist = audioSrcPaths;
    m_currentPlaylistIndex = 0;
    m_errorString.clear();

    emit playlistChanged();
    emit CurrentPlaylistIndexChanged();
    emit errorOccurred();

    setSource(m_playlist.first());

    qCInfo(mediaPlayer) << "Loaded" << m_playlist.size()
                        << "audio files from" << localFolderPath;
}

void AudioPlayer::useLocalLibrary()
{
    setBluetoothMode(false);

    // Make Local Audio the active source again when the user returns
    // to the Local page. Do not start playback automatically.
    const bool wasRadio = m_isRadioMode;
    m_isRadioMode = false;
    setUsbMode(false);
    setRadioReconnecting(false);

    if (wasRadio)
        emit radioModeChanged();

    m_currentStationIndex = -1;
    m_currentStationName.clear();
    m_currentRadioStationCountry.clear();
    emit currentRadioStationNameChanged();
    emit currentRadioStationCountryChanged();

    if (m_playlist.isEmpty()) {
        m_mediaPlayer->stop();
        m_mediaPlayer->setSource(QUrl());
        clearMediaMetaData();
        return;
    }

    if (m_currentPlaylistIndex < 0
            || m_currentPlaylistIndex >= m_playlist.size()) {
        m_currentPlaylistIndex = 0;
        emit CurrentPlaylistIndexChanged();
    }

    setSource(m_playlist.at(m_currentPlaylistIndex));
}

QString AudioPlayer::formatTime(qint64 ms)
{
    if (ms < 0)
        return QStringLiteral("00:00");

    const qint64 totalSeconds = ms / 1000;
    const qint64 hours = totalSeconds / 3600;
    const qint64 minutes = (totalSeconds % 3600) / 60;
    const qint64 seconds = totalSeconds % 60;

    if (hours > 0) {
        return QStringLiteral("%1:%2:%3")
                .arg(hours, 2, 10, QChar('0'))
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));
    }

    return QStringLiteral("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
}

// ============================================================
// Radio source
// ============================================================

void AudioPlayer::playRadioStation(int radio_station_index)
{
    setBluetoothMode(false);

    // index == size is also invalid.
    if (radio_station_index < 0 || radio_station_index >= m_radioStations.size()) {
        setPlaybackError(QStringLiteral("Invalid radio station index"));
        return;
    }

    const QVariantMap station = m_radioStations.at(radio_station_index).toMap();

    // Radio becomes the active source. Keep USB contents in memory but
    // stop treating USB as the active playback source.
    setUsbMode(false);

    const bool wasRadio = m_isRadioMode;
    m_isRadioMode = true;
    m_currentStationIndex = radio_station_index;
    m_currentStationName = station.value(QStringLiteral("name")).toString();
    m_currentRadioStationCountry =
            station.value(QStringLiteral("country")).toString();

    clearMediaMetaData();
    setSource(station.value(QStringLiteral("url")).toString());

    if (!wasRadio)
        emit radioModeChanged();
    emit currentRadioStationNameChanged();
    emit currentRadioStationCountryChanged();

    m_mediaPlayer->play();

    qCInfo(mediaPlayer) << "Tuning to station:" << m_currentStationName;
}

void AudioPlayer::addRadioStation(const QString &name, const QString &url)
{
    const QString cleanName = name.trimmed();
    const QString cleanUrl = url.trimmed();

    if (cleanName.isEmpty() || cleanUrl.isEmpty()) {
        setPlaybackError(QStringLiteral("Station name and URL are required"));
        return;
    }

    const QUrl stationUrl(cleanUrl);
    if (!stationUrl.isValid()) {
        setPlaybackError(QStringLiteral("Invalid radio station URL"));
        return;
    }

    m_radioStations.append(QVariantMap{
        {QStringLiteral("name"), cleanName},
        {QStringLiteral("country"), QStringLiteral("Custom")},
        {QStringLiteral("url"), cleanUrl}
    });

    emit radioStationsChanged();
}

// ============================================================
// USB source
// ============================================================

void AudioPlayer::loadUsbFolder(const QString &folder_path)
{
    setBluetoothMode(false);
    qCDebug(mediaPlayer) << "Incoming USB folder path:" << folder_path;

    const QUrl url(folder_path);
    QString usbFolderPath;
    if (url.isLocalFile())
        usbFolderPath = url.toLocalFile();
    else
        usbFolderPath = folder_path;

    QDir usbDir(usbFolderPath);
    if (!usbDir.exists()) {
        clearUsb();
        setPlaybackError(QStringLiteral("USB folder does not exist: %1")
                         .arg(usbFolderPath));
        return;
    }

    // USB becomes the active source.
    const bool wasRadio = m_isRadioMode;
    m_isRadioMode = false;
    setRadioReconnecting(false);

    if (wasRadio)
        emit radioModeChanged();

    m_currentStationIndex = -1;
    m_currentStationName.clear();
    m_currentRadioStationCountry.clear();
    emit currentRadioStationNameChanged();
    emit currentRadioStationCountryChanged();

    setUsbMode(true);
    setUsbConnected(true);
    setUsbRootPath(usbFolderPath);

    const QStringList filters = {
        QStringLiteral("*.mp3"),
        QStringLiteral("*.wav"),
        QStringLiteral("*.m4a"),
        QStringLiteral("*.aac"),
        QStringLiteral("*.flac"),
        QStringLiteral("*.ogg")
    };

    QStringList usbAudioPaths;

    // Scan the complete USB drive recursively, including Artist/Album folders.
    QDirIterator iterator(usbFolderPath,
                          filters,
                          QDir::Files | QDir::Readable | QDir::NoSymLinks,
                          QDirIterator::Subdirectories);

    while (iterator.hasNext())
        usbAudioPaths.append(iterator.next());

    usbAudioPaths.sort(Qt::CaseInsensitive);
    setUsbTracks(usbAudioPaths);

    if (m_usbTracks.isEmpty()) {
        setCurrentUsbTrackIndex(-1);
        m_mediaPlayer->stop();
        m_mediaPlayer->setSource(QUrl());
        clearMediaMetaData();
        setPlaybackError(QStringLiteral("No Audio Files found on USB: %1")
                         .arg(usbFolderPath));
        return;
    }

    setCurrentUsbTrackIndex(0);
    m_errorString.clear();
    emit errorOccurred();

    // Load the first USB track but do not force playback. This matches
    // the behavior of loadFolder() for Local Audio.
    setSource(m_usbTracks.first());

    qCInfo(mediaPlayer) << "Loaded" << m_usbTracks.size()
                        << "USB audio files from" << usbFolderPath;
}

void AudioPlayer::useUsbLibrary()
{
    setBluetoothMode(false);

    // Make USB the active source whenever the user enters the USB page,
    // even before a drive/folder is chosen. This prevents a previous
    // Local/Radio source from remaining active behind the USB UI.
    const bool wasRadio = m_isRadioMode;
    m_isRadioMode = false;
    setRadioReconnecting(false);

    if (wasRadio)
        emit radioModeChanged();

    m_currentStationIndex = -1;
    m_currentStationName.clear();
    m_currentRadioStationCountry.clear();
    emit currentRadioStationNameChanged();
    emit currentRadioStationCountryChanged();

    setUsbMode(true);

    if (!m_usbConnected || m_usbRootPath.isEmpty()) {
        m_mediaPlayer->stop();
        m_mediaPlayer->setSource(QUrl());
        clearMediaMetaData();
        return;
    }

    const QDir usbDir(m_usbRootPath);
    if (!usbDir.exists()) {
        clearUsb();
        setPlaybackError(QStringLiteral("USB media is no longer available"));
        return;
    }

    setUsbConnected(true);

    if (m_usbTracks.isEmpty()) {
        m_mediaPlayer->stop();
        m_mediaPlayer->setSource(QUrl());
        clearMediaMetaData();
        return;
    }

    if (m_currentUsbTrackIndex < 0
            || m_currentUsbTrackIndex >= m_usbTracks.size()) {
        setCurrentUsbTrackIndex(0);
    }

    const QString usbTrackPath = m_usbTracks.at(m_currentUsbTrackIndex);
    if (!QFileInfo::exists(usbTrackPath)) {
        clearUsb();
        setPlaybackError(QStringLiteral("USB media is no longer available"));
        return;
    }

    setSource(usbTrackPath);
}

void AudioPlayer::playUsbTrack(int usb_track_index)
{
    setBluetoothMode(false);

    if (usb_track_index < 0 || usb_track_index >= m_usbTracks.size()) {
        setPlaybackError(QStringLiteral("Invalid USB track index"));
        return;
    }

    const QString usbTrackPath = m_usbTracks.at(usb_track_index);

    // A USB drive can be removed while the application is running.
    if (!QFileInfo::exists(usbTrackPath)) {
        setPlaybackError(QStringLiteral("USB media is no longer available"));
        clearUsb();
        return;
    }

    const bool wasRadio = m_isRadioMode;
    m_isRadioMode = false;
    setRadioReconnecting(false);

    if (wasRadio)
        emit radioModeChanged();

    setUsbMode(true);
    setUsbConnected(true);
    setCurrentUsbTrackIndex(usb_track_index);

    setSource(usbTrackPath);
    m_mediaPlayer->play();

    qCInfo(mediaPlayer) << "Playing USB file:" << usbTrackPath;
}

void AudioPlayer::clearUsb()
{
    const bool usbWasActive = m_isUsbMode;

    if (usbWasActive)
        m_mediaPlayer->stop();

    setUsbMode(false);
    setUsbConnected(false);
    setUsbRootPath(QString());
    setUsbTracks(QStringList());
    setCurrentUsbTrackIndex(-1);

    if (usbWasActive)
        clearMediaMetaData();

    qCInfo(mediaPlayer) << "USB source cleared";
}

// ============================================================
// Bluetooth source (BlueZ / AVRCP)
// ============================================================

void AudioPlayer::useBluetoothSource()
{
    // Bluetooth audio itself is rendered by the Linux audio stack (BlueZ +
    // PipeWire/PulseAudio). QMediaPlayer must not keep another source active.
    m_mediaPlayer->stop();
    m_mediaPlayer->setSource(QUrl());

    const bool wasRadio = m_isRadioMode;
    m_isRadioMode = false;
    setRadioReconnecting(false);
    setUsbMode(false);

    if (wasRadio)
        emit radioModeChanged();

    m_currentStationIndex = -1;
    m_currentStationName.clear();
    m_currentRadioStationCountry.clear();
    emit currentRadioStationNameChanged();
    emit currentRadioStationCountryChanged();

    setBluetoothMode(true);
    clearMediaMetaData();
    syncBluetoothState(true);

    // Entering the Bluetooth page behaves like the other sources: detect what
    // is already available immediately, and discover only when no phone is
    // currently connected.
    if (m_bluetoothAvailable && !m_bluetoothConnected)
        startBluetoothDiscovery();
}

void AudioPlayer::refreshBluetoothDevices()
{
    syncBluetoothState(true);
}

void AudioPlayer::startBluetoothDiscovery()
{
    syncBluetoothState(true);

    if (!m_bluetoothAvailable || m_bluetoothAdapterPath.isEmpty()) {
        setPlaybackError(QStringLiteral("No Bluetooth adapter is available"));
        return;
    }

    QDBusInterface adapter(kBluezService,
                           m_bluetoothAdapterPath,
                           kAdapterInterface,
                           QDBusConnection::systemBus());
    if (!adapter.isValid()) {
        setPlaybackError(QStringLiteral("Bluetooth adapter is not accessible through BlueZ"));
        return;
    }

    setBluetoothScanning(true);
    auto *watcher = new QDBusPendingCallWatcher(adapter.asyncCall(QStringLiteral("StartDiscovery")), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, watcher](QDBusPendingCallWatcher *) {
        QDBusPendingReply<> reply = *watcher;
        if (reply.isError()
                && reply.error().name() != QStringLiteral("org.bluez.Error.InProgress")) {
            setBluetoothScanning(false);
            setPlaybackError(QStringLiteral("Bluetooth discovery failed: %1")
                             .arg(reply.error().message()));
        } else {
            syncBluetoothState(false);
        }
        watcher->deleteLater();
    });

    if (!m_bluetoothRefreshTimer.isActive())
        m_bluetoothRefreshTimer.start();
}

void AudioPlayer::stopBluetoothDiscovery()
{
    if (m_bluetoothAdapterPath.isEmpty()) {
        setBluetoothScanning(false);
        return;
    }

    QDBusInterface adapter(kBluezService,
                           m_bluetoothAdapterPath,
                           kAdapterInterface,
                           QDBusConnection::systemBus());
    if (!adapter.isValid()) {
        setBluetoothScanning(false);
        return;
    }

    auto *watcher = new QDBusPendingCallWatcher(adapter.asyncCall(QStringLiteral("StopDiscovery")), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, watcher](QDBusPendingCallWatcher *) {
        QDBusPendingReply<> reply = *watcher;
        if (reply.isError()
                && reply.error().name() != QStringLiteral("org.bluez.Error.NotReady")) {
            qCWarning(mediaPlayer) << "Stopping Bluetooth discovery failed:"
                                   << reply.error().message();
        }
        setBluetoothScanning(false);
        syncBluetoothState(false);
        watcher->deleteLater();
    });
}

void AudioPlayer::connectBluetoothDevice(int bluetooth_device_index)
{
    if (bluetooth_device_index < 0
            || bluetooth_device_index >= m_bluetoothDevices.size()) {
        setPlaybackError(QStringLiteral("Invalid Bluetooth device index"));
        return;
    }

    const QVariantMap device = m_bluetoothDevices.at(bluetooth_device_index).toMap();
    const QString devicePath = device.value(QStringLiteral("path")).toString();
    if (devicePath.isEmpty()) {
        setPlaybackError(QStringLiteral("Bluetooth device path is missing"));
        return;
    }

    updateBluetoothDevice(devicePath,
                          device.value(QStringLiteral("name")).toString(),
                          device.value(QStringLiteral("address")).toString());

    if (device.value(QStringLiteral("connected")).toBool()) {
        setBluetoothConnected(true);
        stopBluetoothDiscovery();
        syncBluetoothState(false);
        return;
    }

    const bool pairFirst = !device.value(QStringLiteral("paired")).toBool();
    connectBluetoothPath(devicePath, pairFirst);
}

void AudioPlayer::disconnectBluetoothDevice()
{
    if (m_bluetoothDevicePath.isEmpty()) {
        setBluetoothConnected(false);
        return;
    }

    QDBusInterface device(kBluezService,
                          m_bluetoothDevicePath,
                          kDeviceInterface,
                          QDBusConnection::systemBus());
    if (!device.isValid()) {
        setPlaybackError(QStringLiteral("Selected Bluetooth device is no longer available"));
        clearBluetoothSelection();
        return;
    }

    auto *watcher = new QDBusPendingCallWatcher(device.asyncCall(QStringLiteral("Disconnect")), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, watcher](QDBusPendingCallWatcher *) {
        QDBusPendingReply<> reply = *watcher;
        if (reply.isError()
                && reply.error().name() != QStringLiteral("org.bluez.Error.NotConnected")) {
            setPlaybackError(QStringLiteral("Bluetooth disconnect failed: %1")
                             .arg(reply.error().message()));
        }
        setBluetoothConnected(false);
        m_bluetoothMediaPlayerPath.clear();
        m_bluetoothMediaControlPath.clear();
        updateBluetoothPlaybackState(QStringLiteral("stopped"), 0, 0);
        emit bluetoothMediaControlsAvailableChanged();
        syncBluetoothState(false);
        watcher->deleteLater();
    });
}

void AudioPlayer::setBluetoothMode(bool bluetooth_mode)
{
    if (m_isBluetoothMode == bluetooth_mode)
        return;

    m_isBluetoothMode = bluetooth_mode;
    emit bluetoothModeChanged();

    // Core properties are source-dependent, so switching modes changes what
    // their getters return even when QMediaPlayer itself did not emit a signal.
    emit playingStateChanged();
    emit positionChanged();
    emit durationChanged();

    if (m_isBluetoothMode) {
        if (!m_bluetoothRefreshTimer.isActive())
            m_bluetoothRefreshTimer.start();
    } else if (!m_bluetoothScanning) {
        m_bluetoothRefreshTimer.stop();
    }
}

void AudioPlayer::setBluetoothAvailable(bool available)
{
    if (m_bluetoothAvailable == available)
        return;
    m_bluetoothAvailable = available;
    emit bluetoothAvailableChanged();
}

void AudioPlayer::setBluetoothScanning(bool scanning)
{
    if (m_bluetoothScanning == scanning)
        return;
    m_bluetoothScanning = scanning;
    emit bluetoothScanningChanged();

    if (m_bluetoothScanning) {
        if (!m_bluetoothRefreshTimer.isActive())
            m_bluetoothRefreshTimer.start();
    } else if (!m_isBluetoothMode) {
        m_bluetoothRefreshTimer.stop();
    }
}

void AudioPlayer::setBluetoothConnected(bool connected)
{
    if (m_bluetoothConnected == connected)
        return;
    m_bluetoothConnected = connected;
    emit bluetoothConnectedChanged();
}

void AudioPlayer::updateBluetoothDevice(const QString &path,
                                        const QString &name,
                                        const QString &address)
{
    if (m_bluetoothDevicePath == path
            && m_bluetoothDeviceName == name
            && m_bluetoothDeviceAddress == address) {
        return;
    }

    m_bluetoothDevicePath = path;
    m_bluetoothDeviceName = name;
    m_bluetoothDeviceAddress = address;
    emit bluetoothDeviceChanged();
}

void AudioPlayer::updateBluetoothPlaybackState(const QString &status,
                                               qint64 position,
                                               qint64 duration)
{
    const QString normalizedStatus = status.isEmpty()
            ? QStringLiteral("stopped") : status;
    const bool playing = normalizedStatus == QStringLiteral("playing")
            || normalizedStatus == QStringLiteral("forward-seek")
            || normalizedStatus == QStringLiteral("reverse-seek");

    if (m_bluetoothPlaybackStatus != normalizedStatus) {
        m_bluetoothPlaybackStatus = normalizedStatus;
        emit bluetoothPlaybackStatusChanged();
    }

    if (m_bluetoothPlaying != playing) {
        m_bluetoothPlaying = playing;
        if (m_isBluetoothMode)
            emit playingStateChanged();
    }

    position = qMax<qint64>(0, position);
    duration = qMax<qint64>(0, duration);

    if (m_bluetoothPosition != position) {
        m_bluetoothPosition = position;
        if (m_isBluetoothMode)
            emit positionChanged();
    }

    if (m_bluetoothDuration != duration) {
        m_bluetoothDuration = duration;
        if (m_isBluetoothMode)
            emit durationChanged();
    }
}

void AudioPlayer::syncBluetoothState(bool report_errors)
{
    QDBusConnection bus = QDBusConnection::systemBus();
    if (!bus.isConnected()) {
        setBluetoothAvailable(false);
        setBluetoothScanning(false);
        setBluetoothConnected(false);
        if (report_errors)
            setPlaybackError(QStringLiteral("System D-Bus is unavailable; Bluetooth cannot be queried"));
        return;
    }

    QDBusInterface manager(kBluezService,
                           QStringLiteral("/"),
                           kObjectManagerInterface,
                           bus);
    if (!manager.isValid()) {
        setBluetoothAvailable(false);
        setBluetoothScanning(false);
        setBluetoothConnected(false);
        if (report_errors)
            setPlaybackError(QStringLiteral("BlueZ is not running or org.bluez is unavailable"));
        return;
    }

    QDBusReply<BluezManagedObjects> managedReply = manager.call(QStringLiteral("GetManagedObjects"));
    if (!managedReply.isValid()) {
        setBluetoothAvailable(false);
        if (report_errors) {
            setPlaybackError(QStringLiteral("Unable to read Bluetooth devices from BlueZ: %1")
                             .arg(managedReply.error().message()));
        }
        return;
    }

    const BluezManagedObjects objects = managedReply.value();
    QString adapterPath;
    bool discovering = false;
    QVariantList devices;
    QString preferredConnectedPath;
    QString preferredConnectedName;
    QString preferredConnectedAddress;
    int preferredConnectedScore = -1;
    bool selectedStillExists = false;
    bool selectedConnected = false;
    QString selectedName;
    QString selectedAddress;

    // Associate MediaPlayer1 objects with their owning Device1 before picking
    // a connected device. This prevents an unrelated connected peripheral from
    // being shown as the Bluetooth audio source.
    QSet<QString> mediaPlayerDevicePaths;
    for (auto objectIt = objects.cbegin(); objectIt != objects.cend(); ++objectIt) {
        const auto playerIt = objectIt.value().constFind(
                    QString::fromLatin1(kMediaPlayerInterface));
        if (playerIt == objectIt.value().cend())
            continue;

        const QString devicePath = mediaPlayerDevicePath(
                    objectIt.key().path(), playerIt.value());
        if (!devicePath.isEmpty())
            mediaPlayerDevicePaths.insert(devicePath);
    }

    for (auto objectIt = objects.cbegin(); objectIt != objects.cend(); ++objectIt) {
        const QString objectPath = objectIt.key().path();
        const BluezInterfaceMap &interfaces = objectIt.value();

        const auto adapterIt = interfaces.constFind(QString::fromLatin1(kAdapterInterface));
        if (adapterIt != interfaces.cend() && adapterPath.isEmpty()) {
            adapterPath = objectPath;
            discovering = dbusBool(
                        adapterIt.value().value(QStringLiteral("Discovering")));
        }

        const auto deviceIt = interfaces.constFind(QString::fromLatin1(kDeviceInterface));
        if (deviceIt == interfaces.cend())
            continue;

        const QVariantMap &properties = deviceIt.value();
        const QString address = dbusString(
                    properties.value(QStringLiteral("Address")));
        const QString name = bluetoothDeviceName(properties);

        const bool connected = dbusBool(
                    properties.value(QStringLiteral("Connected")));
        const bool paired = dbusBool(
                    properties.value(QStringLiteral("Paired")));
        const bool trusted = dbusBool(
                    properties.value(QStringLiteral("Trusted")));
        const int rssi = dbusInt(
                    properties.value(QStringLiteral("RSSI")), -127);
        const bool audioCapable = isBluetoothAudioDevice(properties)
                || interfaces.contains(QString::fromLatin1(kMediaControlInterface))
                || mediaPlayerDevicePaths.contains(objectPath);

        QVariantMap deviceModel{
            {QStringLiteral("path"), objectPath},
            {QStringLiteral("name"), name},
            {QStringLiteral("address"), address},
            {QStringLiteral("connected"), connected},
            {QStringLiteral("paired"), paired},
            {QStringLiteral("trusted"), trusted},
            {QStringLiteral("audioCapable"), audioCapable},
            {QStringLiteral("rssi"), rssi}
        };
        devices.append(deviceModel);

        if (connected) {
            int score = 0;
            if (audioCapable)
                score += 100;
            if (interfaces.contains(QString::fromLatin1(kMediaControlInterface)))
                score += 100;
            if (mediaPlayerDevicePaths.contains(objectPath))
                score += 200;
            if (objectPath == m_bluetoothDevicePath)
                score += 10;

            if (score > preferredConnectedScore) {
                preferredConnectedScore = score;
                preferredConnectedPath = objectPath;
                preferredConnectedName = name;
                preferredConnectedAddress = address;
            }
        }

        if (objectPath == m_bluetoothDevicePath) {
            selectedStillExists = true;
            selectedConnected = connected;
            selectedName = name;
            selectedAddress = address;
        }
    }

    std::sort(devices.begin(), devices.end(), [](const QVariant &left, const QVariant &right) {
        const QVariantMap a = left.toMap();
        const QVariantMap b = right.toMap();
        if (a.value(QStringLiteral("connected")).toBool()
                != b.value(QStringLiteral("connected")).toBool()) {
            return a.value(QStringLiteral("connected")).toBool();
        }
        if (a.value(QStringLiteral("paired")).toBool()
                != b.value(QStringLiteral("paired")).toBool()) {
            return a.value(QStringLiteral("paired")).toBool();
        }
        return a.value(QStringLiteral("name")).toString().compare(
                    b.value(QStringLiteral("name")).toString(), Qt::CaseInsensitive) < 0;
    });

    m_bluetoothAdapterPath = adapterPath;
    setBluetoothAvailable(!adapterPath.isEmpty());
    setBluetoothScanning(discovering);

    if (m_bluetoothDevices != devices) {
        m_bluetoothDevices = devices;
        emit bluetoothDevicesChanged();
    }

    // Prefer the user's selected device. If there is no selection, adopt an
    // already-connected phone automatically when the Bluetooth source opens.
    if (!m_bluetoothDevicePath.isEmpty()
            && selectedStillExists
            && selectedConnected
            && (preferredConnectedPath.isEmpty()
                || preferredConnectedPath == m_bluetoothDevicePath
                || preferredConnectedScore < 100)) {
        updateBluetoothDevice(m_bluetoothDevicePath, selectedName, selectedAddress);
        setBluetoothConnected(true);
    } else if (!preferredConnectedPath.isEmpty()) {
        updateBluetoothDevice(preferredConnectedPath,
                              preferredConnectedName,
                              preferredConnectedAddress);
        setBluetoothConnected(true);
    } else {
        if (!m_bluetoothDevicePath.isEmpty() && selectedStillExists) {
            updateBluetoothDevice(m_bluetoothDevicePath, selectedName, selectedAddress);
        } else if (!m_bluetoothDevicePath.isEmpty()) {
            clearBluetoothSelection(true);
        }
        setBluetoothConnected(false);
    }

    const bool controlsWereAvailable = getBluetoothMediaControlsAvailable();
    QString mediaPlayerPath;
    QString mediaControlPath;
    QString playbackStatus = QStringLiteral("stopped");
    qint64 position = 0;
    qint64 duration = 0;
    QVariantMap track;

    if (m_bluetoothConnected && !m_bluetoothDevicePath.isEmpty()) {
        const auto selectedObject = objects.constFind(QDBusObjectPath(m_bluetoothDevicePath));
        if (selectedObject != objects.cend()
                && selectedObject.value().contains(QString::fromLatin1(kMediaControlInterface))) {
            mediaControlPath = m_bluetoothDevicePath;
        }

        for (auto objectIt = objects.cbegin(); objectIt != objects.cend(); ++objectIt) {
            const BluezInterfaceMap &interfaces = objectIt.value();
            const auto playerIt = interfaces.constFind(QString::fromLatin1(kMediaPlayerInterface));
            if (playerIt == interfaces.cend())
                continue;

            const QVariantMap &properties = playerIt.value();
            const QString playerDevicePath = mediaPlayerDevicePath(
                        objectIt.key().path(), properties);
            if (playerDevicePath != m_bluetoothDevicePath)
                continue;

            mediaPlayerPath = objectIt.key().path();
            playbackStatus = properties.value(QStringLiteral("Status")).toString();
            position = variantToInt64(properties.value(QStringLiteral("Position")));
            track = dbusVariantMap(properties.value(QStringLiteral("Track")));
            duration = variantToInt64(track.value(QStringLiteral("Duration")));
            break;
        }
    }

    m_bluetoothMediaPlayerPath = mediaPlayerPath;
    m_bluetoothMediaControlPath = mediaControlPath;
    if (controlsWereAvailable != getBluetoothMediaControlsAvailable())
        emit bluetoothMediaControlsAvailableChanged();

    updateBluetoothPlaybackState(playbackStatus, position, duration);

    if (m_isBluetoothMode) {
        const QString newTitle = track.value(QStringLiteral("Title")).toString();
        const QString newAuthor = track.value(QStringLiteral("Artist")).toString();
        const QString newAlbum = track.value(QStringLiteral("Album")).toString();
        const QString newGenre = track.value(QStringLiteral("Genre")).toString();

        if (m_audioTitle != newTitle
                || m_audioAuthor != newAuthor
                || m_audioAlbum != newAlbum
                || m_audioType != newGenre) {
            m_audioTitle = newTitle;
            m_audioAuthor = newAuthor;
            m_audioAlbum = newAlbum;
            m_audioType = newGenre;
            emit metaDataChanged();
        }
    }
}

void AudioPlayer::sendBluetoothMediaCommand(const QString &command)
{
    if (!m_bluetoothConnected) {
        setPlaybackError(QStringLiteral("No Bluetooth phone is connected"));
        return;
    }

    QString path = m_bluetoothMediaPlayerPath;
    QString interfaceName = QString::fromLatin1(kMediaPlayerInterface);
    if (path.isEmpty()) {
        path = m_bluetoothMediaControlPath;
        interfaceName = QString::fromLatin1(kMediaControlInterface);
    }

    if (path.isEmpty()) {
        setPlaybackError(QStringLiteral("The connected Bluetooth device has no AVRCP media controls yet"));
        return;
    }

    QDBusInterface player(kBluezService,
                          path,
                          interfaceName,
                          QDBusConnection::systemBus());
    if (!player.isValid()) {
        setPlaybackError(QStringLiteral("Bluetooth media controller is unavailable"));
        return;
    }

    auto *watcher = new QDBusPendingCallWatcher(player.asyncCall(command), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, watcher, command](QDBusPendingCallWatcher *) {
        QDBusPendingReply<> reply = *watcher;
        if (reply.isError()) {
            setPlaybackError(QStringLiteral("Bluetooth %1 command failed: %2")
                             .arg(command, reply.error().message()));
        } else {
            QTimer::singleShot(120, this, [this]() { syncBluetoothState(false); });
        }
        watcher->deleteLater();
    });
}

void AudioPlayer::connectBluetoothPath(const QString &device_path, bool pair_first)
{
    if (device_path.isEmpty())
        return;

    QDBusInterface device(kBluezService,
                          device_path,
                          kDeviceInterface,
                          QDBusConnection::systemBus());
    if (!device.isValid()) {
        setPlaybackError(QStringLiteral("Bluetooth device is no longer available"));
        return;
    }

    if (pair_first) {
        auto *pairWatcher = new QDBusPendingCallWatcher(device.asyncCall(QStringLiteral("Pair")), this);
        connect(pairWatcher, &QDBusPendingCallWatcher::finished, this,
                [this, pairWatcher, device_path](QDBusPendingCallWatcher *) {
            QDBusPendingReply<> pairReply = *pairWatcher;
            const bool alreadyPaired = pairReply.isError()
                    && pairReply.error().name() == QStringLiteral("org.bluez.Error.AlreadyExists");
            if (pairReply.isError() && !alreadyPaired) {
                setPlaybackError(QStringLiteral("Bluetooth pairing failed: %1")
                                 .arg(pairReply.error().message()));
            } else {
                connectBluetoothPath(device_path, false);
            }
            pairWatcher->deleteLater();
        });
        return;
    }

    auto *connectWatcher = new QDBusPendingCallWatcher(device.asyncCall(QStringLiteral("Connect")), this);
    connect(connectWatcher, &QDBusPendingCallWatcher::finished, this,
            [this, connectWatcher](QDBusPendingCallWatcher *) {
        QDBusPendingReply<> connectReply = *connectWatcher;
        const bool alreadyConnected = connectReply.isError()
                && connectReply.error().name() == QStringLiteral("org.bluez.Error.AlreadyConnected");
        if (connectReply.isError() && !alreadyConnected) {
            setPlaybackError(QStringLiteral("Bluetooth connection failed: %1")
                             .arg(connectReply.error().message()));
        } else {
            setBluetoothConnected(true);
            stopBluetoothDiscovery();
            QTimer::singleShot(350, this, [this]() { syncBluetoothState(false); });
        }
        connectWatcher->deleteLater();
    });
}

void AudioPlayer::clearBluetoothSelection(bool keep_device_list)
{
    const bool controlsWereAvailable = getBluetoothMediaControlsAvailable();
    const bool hadDevice = !m_bluetoothDevicePath.isEmpty()
            || !m_bluetoothDeviceName.isEmpty()
            || !m_bluetoothDeviceAddress.isEmpty();

    m_bluetoothDevicePath.clear();
    m_bluetoothDeviceName.clear();
    m_bluetoothDeviceAddress.clear();
    m_bluetoothMediaPlayerPath.clear();
    m_bluetoothMediaControlPath.clear();
    setBluetoothConnected(false);
    updateBluetoothPlaybackState(QStringLiteral("stopped"), 0, 0);

    if (hadDevice)
        emit bluetoothDeviceChanged();
    if (controlsWereAvailable)
        emit bluetoothMediaControlsAvailableChanged();

    if (!keep_device_list && !m_bluetoothDevices.isEmpty()) {
        m_bluetoothDevices.clear();
        emit bluetoothDevicesChanged();
    }

    if (m_isBluetoothMode)
        clearMediaMetaData();
}

// ============================================================
// Private helpers
// ============================================================

void AudioPlayer::setSource(const QString &audioSource)
{
    m_mediaPlayer->stop();

    if (!m_errorString.isEmpty()) {
        m_errorString.clear();
        emit errorOccurred();
    }

    clearMediaMetaData();

    const QUrl candidate(audioSource);
    if (candidate.isLocalFile()) {
        m_mediaPlayer->setSource(candidate);
        return;
    }

    // QFileInfo handles ordinary absolute local paths returned by QDir/QDirIterator.
    const QFileInfo localFile(audioSource);
    if (localFile.isAbsolute() && localFile.exists()) {
        m_mediaPlayer->setSource(QUrl::fromLocalFile(audioSource));
        return;
    }

    m_mediaPlayer->setSource(candidate);
}

void AudioPlayer::clearMediaMetaData()
{
    m_audioTitle.clear();
    m_audioAuthor.clear();
    m_audioAlbum.clear();
    m_audioType.clear();

    // Emit our wrapper signal so QML updates immediately.
    emit metaDataChanged();
}

void AudioPlayer::previousRadio()
{
    if (m_radioStations.isEmpty()) {
        setPlaybackError(QStringLiteral("No stations available"));
        return;
    }

    if (!m_isRadioMode) {
        setPlaybackError(QStringLiteral("Radio mode is not active"));
        return;
    }

    m_currentStationIndex =
            (m_currentStationIndex - 1 + m_radioStations.size())
            % m_radioStations.size();
    playRadioStation(m_currentStationIndex);
}

void AudioPlayer::nextRadio()
{
    if (m_radioStations.isEmpty()) {
        setPlaybackError(QStringLiteral("No stations available"));
        return;
    }

    if (!m_isRadioMode) {
        setPlaybackError(QStringLiteral("Radio mode is not active"));
        return;
    }

    m_currentStationIndex =
            (m_currentStationIndex + 1) % m_radioStations.size();
    playRadioStation(m_currentStationIndex);
}

void AudioPlayer::setRadioReconnecting(bool reconnecting)
{
    if (m_radioReconnecting == reconnecting)
        return;

    m_radioReconnecting = reconnecting;
    emit radioReconnectingStateChanged();
}

void AudioPlayer::setPlaybackError(const QString &message)
{
    m_errorString = message;
    qCWarning(mediaPlayer) << "Playback error:" << m_errorString;
    emit errorOccurred();
}
