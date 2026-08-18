#include "soniqueplaybackengine.h"

#include <QDir>
#include <QFileInfo>
#include <QLoggingCategory>
#include <QMediaMetaData>

Q_LOGGING_CATEGORY(soniquePlayback, "sonique.playback")

SoniquePlaybackEngine::SoniquePlaybackEngine(QObject *parent)
    : QObject(parent),
      m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this))
{
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.70f);

    connect(m_player, &QMediaPlayer::positionChanged,
            this, &SoniquePlaybackEngine::playheadChanged);
    connect(m_player, &QMediaPlayer::durationChanged,
            this, &SoniquePlaybackEngine::mediaLengthChanged);
    connect(m_player, &QMediaPlayer::playbackStateChanged,
            this, &SoniquePlaybackEngine::playbackActiveChanged);
    connect(m_audioOutput, &QAudioOutput::mutedChanged,
            this, &SoniquePlaybackEngine::silenceEnabledChanged);
    connect(m_audioOutput, &QAudioOutput::volumeChanged,
            this, &SoniquePlaybackEngine::outputLevelChanged);

    connect(m_player, &QMediaPlayer::errorOccurred, this,
            [this](QMediaPlayer::Error error, const QString &message) {
        if (error != QMediaPlayer::NoError)
            reportError(message.isEmpty() ? tr("Unknown playback error") : message);
    });

    connect(m_player, &QMediaPlayer::metaDataChanged, this, [this]() {
        const QMediaMetaData metadata = m_player->metaData();
        m_trackTitle = metadata.stringValue(QMediaMetaData::Title);
        m_trackArtist = metadata.stringValue(QMediaMetaData::ContributingArtist);
        m_trackAlbum = metadata.stringValue(QMediaMetaData::AlbumTitle);
        m_trackGenre = metadata.stringValue(QMediaMetaData::Genre);

        if (m_trackTitle.isEmpty() && !m_radioActive
                && m_selectedTrackIndex >= 0
                && m_selectedTrackIndex < m_localTracks.size()) {
            m_trackTitle = QFileInfo(m_localTracks.at(m_selectedTrackIndex)).completeBaseName();
        }
        emit trackDetailsChanged();
    });

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this,
            [this](QMediaPlayer::MediaStatus status) {
        const bool waiting = status == QMediaPlayer::LoadingMedia
                || status == QMediaPlayer::BufferingMedia
                || status == QMediaPlayer::StalledMedia;
        setStreamBuffering(m_radioActive && waiting);

        if (status == QMediaPlayer::EndOfMedia)
            playNext();
    });

    m_stationCatalog = {
        QVariantMap{{"name", "Quran Radio Cairo"},
                    {"country", "Egypt"},
                    {"url", "http://n12.radiojar.com/8s5u5tpdtwzuv"}},
        QVariantMap{{"name", "Saudi Quran Radio"},
                    {"country", "Saudi Arabia"},
                    {"url", "http://live.mp3quran.net:8008/"}},
        QVariantMap{{"name", "Quran Radio Nablus"},
                    {"country", "Palestine"},
                    {"url", "http://www.quran-radio.org:8002/"}},
        QVariantMap{{"name", "Quran Radio"},
                    {"country", "Saudi Arabia"},
                    {"url", "http://live.mp3quran.net:8002/"}}
    };
}

bool SoniquePlaybackEngine::isPlaybackActive() const
{
    return m_player->playbackState() == QMediaPlayer::PlayingState;
}

qint64 SoniquePlaybackEngine::playhead() const { return m_player->position(); }
qint64 SoniquePlaybackEngine::mediaLength() const { return m_player->duration(); }
bool SoniquePlaybackEngine::isSilenced() const { return m_audioOutput->isMuted(); }
float SoniquePlaybackEngine::outputLevel() const { return m_audioOutput->volume(); }
QStringList SoniquePlaybackEngine::localTracks() const { return m_localTracks; }
int SoniquePlaybackEngine::selectedTrackIndex() const { return m_selectedTrackIndex; }
QString SoniquePlaybackEngine::trackTitle() const { return m_trackTitle; }
QString SoniquePlaybackEngine::trackArtist() const { return m_trackArtist; }
QString SoniquePlaybackEngine::trackAlbum() const { return m_trackAlbum; }
QString SoniquePlaybackEngine::trackGenre() const { return m_trackGenre; }
QString SoniquePlaybackEngine::lastPlaybackError() const { return m_lastPlaybackError; }
bool SoniquePlaybackEngine::isRadioActive() const { return m_radioActive; }
QVariantList SoniquePlaybackEngine::stationCatalog() const { return m_stationCatalog; }
QString SoniquePlaybackEngine::tunedStationName() const { return m_tunedStationName; }
QString SoniquePlaybackEngine::tunedStationCountry() const { return m_tunedStationCountry; }
bool SoniquePlaybackEngine::isStreamBuffering() const { return m_streamBuffering; }

void SoniquePlaybackEngine::setSilenced(bool enabled)
{
    m_audioOutput->setMuted(enabled);
}

void SoniquePlaybackEngine::setOutputLevel(float level)
{
    m_audioOutput->setVolume(qBound(0.0f, level, 1.0f));
}

void SoniquePlaybackEngine::togglePlayback()
{
    if (isPlaybackActive())
        m_player->pause();
    else
        m_player->play();
}

void SoniquePlaybackEngine::stopPlayback()
{
    m_player->stop();
}

void SoniquePlaybackEngine::playNext()
{
    if (m_radioActive) {
        if (m_stationCatalog.isEmpty()) {
            reportError(tr("No radio stations are available."));
            return;
        }
        tuneStation((m_tunedStationIndex + 1) % m_stationCatalog.size());
        return;
    }

    if (m_localTracks.isEmpty()) {
        reportError(tr("Choose a folder containing audio files first."));
        return;
    }

    m_selectedTrackIndex = (m_selectedTrackIndex + 1) % m_localTracks.size();
    emit selectedTrackIndexChanged();
    openMedia(QUrl::fromLocalFile(m_localTracks.at(m_selectedTrackIndex)));
    m_player->play();
}

void SoniquePlaybackEngine::playPrevious()
{
    if (m_radioActive) {
        if (m_stationCatalog.isEmpty()) {
            reportError(tr("No radio stations are available."));
            return;
        }
        const int previous = (m_tunedStationIndex - 1 + m_stationCatalog.size())
                % m_stationCatalog.size();
        tuneStation(previous);
        return;
    }

    if (m_localTracks.isEmpty()) {
        reportError(tr("Choose a folder containing audio files first."));
        return;
    }

    m_selectedTrackIndex = (m_selectedTrackIndex - 1 + m_localTracks.size())
            % m_localTracks.size();
    emit selectedTrackIndexChanged();
    openMedia(QUrl::fromLocalFile(m_localTracks.at(m_selectedTrackIndex)));
    m_player->play();
}

void SoniquePlaybackEngine::seekTo(qint64 milliseconds)
{
    if (milliseconds < 0 || milliseconds > mediaLength()) {
        reportError(tr("The requested playback position is outside this track."));
        return;
    }
    m_player->setPosition(milliseconds);
}

void SoniquePlaybackEngine::loadLocalFolder(const QUrl &folderUrl)
{
    const QString folderPath = folderUrl.isLocalFile()
            ? folderUrl.toLocalFile() : folderUrl.toString();
    const QDir directory(folderPath);

    if (!directory.exists()) {
        reportError(tr("Folder does not exist: %1").arg(folderPath));
        return;
    }

    const QStringList filters = {"*.mp3", "*.wav", "*.m4a", "*.aac", "*.flac", "*.ogg"};
    const QFileInfoList files = directory.entryInfoList(
            filters, QDir::Files | QDir::Readable, QDir::Name);

    if (files.isEmpty()) {
        reportError(tr("No supported audio files were found in: %1").arg(folderPath));
        return;
    }

    m_localTracks.clear();
    for (const QFileInfo &file : files)
        m_localTracks.append(file.absoluteFilePath());

    m_selectedTrackIndex = 0;
    setRadioActive(false);
    m_tunedStationIndex = -1;
    m_tunedStationName.clear();
    m_tunedStationCountry.clear();
    m_lastPlaybackError.clear();

    emit localTracksChanged();
    emit selectedTrackIndexChanged();
    emit tunedStationChanged();
    emit playbackErrorChanged();

    openMedia(QUrl::fromLocalFile(m_localTracks.first()));
    qCInfo(soniquePlayback) << "Loaded" << m_localTracks.size()
                           << "tracks from" << folderPath;
}

void SoniquePlaybackEngine::useLocalLibrary()
{
    if (!m_radioActive)
        return;

    m_player->stop();
    setRadioActive(false);
    m_tunedStationIndex = -1;
    m_tunedStationName.clear();
    m_tunedStationCountry.clear();
    emit tunedStationChanged();

    if (m_selectedTrackIndex >= 0 && m_selectedTrackIndex < m_localTracks.size())
        openMedia(QUrl::fromLocalFile(m_localTracks.at(m_selectedTrackIndex)));
    else
        clearTrackDetails();
}

QString SoniquePlaybackEngine::formatClock(qint64 milliseconds) const
{
    if (milliseconds < 0)
        return QStringLiteral("00:00");

    const qint64 totalSeconds = milliseconds / 1000;
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

void SoniquePlaybackEngine::tuneStation(int stationIndex)
{
    if (stationIndex < 0 || stationIndex >= m_stationCatalog.size()) {
        reportError(tr("Invalid radio station number."));
        return;
    }

    const QVariantMap station = m_stationCatalog.at(stationIndex).toMap();
    m_tunedStationIndex = stationIndex;
    m_tunedStationName = station.value("name").toString();
    m_tunedStationCountry = station.value("country").toString();
    setRadioActive(true);
    clearTrackDetails();
    emit tunedStationChanged();

    openMedia(QUrl(station.value("url").toString()));
    m_player->play();
}

void SoniquePlaybackEngine::saveStation(const QString &name,
                                        const QString &country,
                                        const QUrl &streamUrl)
{
    if (name.trimmed().isEmpty() || !streamUrl.isValid() || streamUrl.isEmpty()) {
        reportError(tr("A station needs a name and a valid stream URL."));
        return;
    }

    m_stationCatalog.append(QVariantMap{{"name", name.trimmed()},
                                        {"country", country.trimmed()},
                                        {"url", streamUrl.toString()}});
    emit stationCatalogChanged();
}

void SoniquePlaybackEngine::openMedia(const QUrl &source)
{
    m_player->stop();
    m_lastPlaybackError.clear();
    emit playbackErrorChanged();
    m_player->setSource(source);
}

void SoniquePlaybackEngine::clearTrackDetails()
{
    m_trackTitle.clear();
    m_trackArtist.clear();
    m_trackAlbum.clear();
    m_trackGenre.clear();
    emit trackDetailsChanged();
}

void SoniquePlaybackEngine::setRadioActive(bool enabled)
{
    if (m_radioActive == enabled)
        return;
    m_radioActive = enabled;
    emit radioActiveChanged();
}

void SoniquePlaybackEngine::setStreamBuffering(bool buffering)
{
    if (m_streamBuffering == buffering)
        return;
    m_streamBuffering = buffering;
    emit streamBufferingChanged();
}

void SoniquePlaybackEngine::reportError(const QString &message)
{
    m_lastPlaybackError = message;
    qCWarning(soniquePlayback) << message;
    emit playbackErrorChanged();
}
