#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include <QStringList>
#include <QTimer>
#include <QVariantList>
#include <QtQml/qqml.h>

class AudioPlayer : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // 1. Core playback properties
    Q_PROPERTY(bool playing READ getPlayingState NOTIFY playingStateChanged FINAL)
    Q_PROPERTY(qint64 position READ getPosition WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(qint64 duration READ getDuration NOTIFY durationChanged FINAL)

    // 2. Audio output properties
    Q_PROPERTY(bool muted READ getMuteState WRITE setMuteState NOTIFY muteStateChanged FINAL)
    Q_PROPERTY(float volume READ getVolume WRITE setVolume NOTIFY volumeChanged FINAL)

    // 3. Local source properties
    Q_PROPERTY(QStringList playlist READ getPlaylist NOTIFY playlistChanged FINAL)
    Q_PROPERTY(int currentPlaylistIndex READ getCurrentPlaylistIndex
               NOTIFY CurrentPlaylistIndexChanged FINAL)

    // 4. Radio source properties
    Q_PROPERTY(bool isRadioMode READ getRadioMode NOTIFY radioModeChanged FINAL)
    Q_PROPERTY(QVariantList radioStations READ getRadioStations NOTIFY radioStationsChanged FINAL)
    Q_PROPERTY(QString currentRadioStationName READ getCurrentRadioStationName
               NOTIFY currentRadioStationNameChanged FINAL)
    Q_PROPERTY(QString currentRadioStationCountry READ getCurrentStationCountry
               NOTIFY currentRadioStationCountryChanged FINAL)
    Q_PROPERTY(bool radioReconnecting READ getRadioReconnectingState
               NOTIFY radioReconnectingStateChanged FINAL)

    // 5. USB source properties
    Q_PROPERTY(bool isUsbMode READ getUsbMode NOTIFY usbModeChanged FINAL)
    Q_PROPERTY(bool usbConnected READ getUsbConnected NOTIFY usbConnectedChanged FINAL)
    Q_PROPERTY(QString usbRootPath READ getUsbRootPath NOTIFY usbRootPathChanged FINAL)
    Q_PROPERTY(QStringList usbTracks READ getUsbTracks NOTIFY usbTracksChanged FINAL)
    Q_PROPERTY(int currentUsbTrackIndex READ getCurrentUsbTrackIndex
               NOTIFY currentUsbTrackIndexChanged FINAL)

    // 6. Bluetooth source properties (BlueZ / AVRCP backend)
    Q_PROPERTY(bool isBluetoothMode READ getBluetoothMode NOTIFY bluetoothModeChanged FINAL)
    Q_PROPERTY(bool bluetoothAvailable READ getBluetoothAvailable NOTIFY bluetoothAvailableChanged FINAL)
    Q_PROPERTY(bool bluetoothScanning READ getBluetoothScanning NOTIFY bluetoothScanningChanged FINAL)
    Q_PROPERTY(bool bluetoothConnected READ getBluetoothConnected NOTIFY bluetoothConnectedChanged FINAL)
    Q_PROPERTY(QVariantList bluetoothDevices READ getBluetoothDevices NOTIFY bluetoothDevicesChanged FINAL)
    Q_PROPERTY(QString bluetoothDeviceName READ getBluetoothDeviceName NOTIFY bluetoothDeviceChanged FINAL)
    Q_PROPERTY(QString bluetoothDeviceAddress READ getBluetoothDeviceAddress NOTIFY bluetoothDeviceChanged FINAL)
    Q_PROPERTY(QString bluetoothPlaybackStatus READ getBluetoothPlaybackStatus
               NOTIFY bluetoothPlaybackStatusChanged FINAL)
    Q_PROPERTY(bool bluetoothMediaControlsAvailable READ getBluetoothMediaControlsAvailable
               NOTIFY bluetoothMediaControlsAvailableChanged FINAL)

    // 7. Media metadata and errors
    Q_PROPERTY(QString audioTitle READ getAudioTitle NOTIFY metaDataChanged FINAL)
    Q_PROPERTY(QString audioAuthor READ getAudioAuthor NOTIFY metaDataChanged FINAL)
    Q_PROPERTY(QString audioAlbum READ getAudioAlbum NOTIFY metaDataChanged FINAL)
    Q_PROPERTY(QString audioType READ getAudioType NOTIFY metaDataChanged FINAL)
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorOccurred FINAL)

public:
    explicit AudioPlayer(QObject *parent = nullptr);

    // Getters: core playback
    bool getPlayingState() const;
    qint64 getPosition() const;
    qint64 getDuration() const;

    // Getters: audio output
    bool getMuteState() const;
    float getVolume() const;

    // Getters: local source
    QStringList getPlaylist() const;
    int getCurrentPlaylistIndex() const;

    // Getters: radio source
    bool getRadioMode() const;
    QVariantList getRadioStations() const;
    QString getCurrentRadioStationName() const;
    QString getCurrentStationCountry() const;
    bool getRadioReconnectingState() const;

    // Getters: USB source
    bool getUsbMode() const;
    bool getUsbConnected() const;
    QString getUsbRootPath() const;
    QStringList getUsbTracks() const;
    int getCurrentUsbTrackIndex() const;

    // Getters: Bluetooth source
    bool getBluetoothMode() const;
    bool getBluetoothAvailable() const;
    bool getBluetoothScanning() const;
    bool getBluetoothConnected() const;
    QVariantList getBluetoothDevices() const;
    QString getBluetoothDeviceName() const;
    QString getBluetoothDeviceAddress() const;
    QString getBluetoothPlaybackStatus() const;
    bool getBluetoothMediaControlsAvailable() const;

    // Getters: metadata / error
    QString getAudioTitle() const;
    QString getAudioAuthor() const;
    QString getAudioAlbum() const;
    QString getAudioType() const;
    QString getErrorString() const;

    // Setters: core / audio output
    void setPosition(qint64 position_ms);
    void setMuteState(bool mute_state);
    void setVolume(float volume_level);

    // Setters: USB source state
    void setUsbMode(bool usb_mode);
    void setUsbConnected(bool connected);
    void setUsbRootPath(const QString &usb_root_path);
    void setUsbTracks(const QStringList &usb_tracks);
    void setCurrentUsbTrackIndex(int usb_track_index);

    // Playback / local-audio control methods
    Q_INVOKABLE void playPause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void loadFolder(const QString &folder_path);
    Q_INVOKABLE void useLocalLibrary();
    Q_INVOKABLE QString formatTime(qint64 ms);

    // Radio control methods
    Q_INVOKABLE void playRadioStation(int radio_station_index);
    Q_INVOKABLE void addRadioStation(const QString &name, const QString &url);

    // USB control methods
    Q_INVOKABLE void loadUsbFolder(const QString &folder_path);
    Q_INVOKABLE void useUsbLibrary();
    Q_INVOKABLE void playUsbTrack(int usb_track_index);
    Q_INVOKABLE void clearUsb();

    // Bluetooth control methods
    Q_INVOKABLE void useBluetoothSource();
    Q_INVOKABLE void refreshBluetoothDevices();
    Q_INVOKABLE void startBluetoothDiscovery();
    Q_INVOKABLE void stopBluetoothDiscovery();
    Q_INVOKABLE void connectBluetoothDevice(int bluetooth_device_index);
    Q_INVOKABLE void disconnectBluetoothDevice();

signals:
    // Signals: core playback / audio output
    void playingStateChanged();
    void positionChanged();
    void durationChanged();
    void muteStateChanged();
    void volumeChanged();

    // Signals: local source
    void playlistChanged();
    void CurrentPlaylistIndexChanged();

    // Signals: radio source
    void radioModeChanged();
    void radioStationsChanged();
    void currentRadioStationNameChanged();
    void currentRadioStationCountryChanged();
    void radioReconnectingStateChanged();

    // Signals: USB source
    void usbModeChanged();
    void usbConnectedChanged();
    void usbRootPathChanged();
    void usbTracksChanged();
    void currentUsbTrackIndexChanged();

    // Signals: Bluetooth source
    void bluetoothModeChanged();
    void bluetoothAvailableChanged();
    void bluetoothScanningChanged();
    void bluetoothConnectedChanged();
    void bluetoothDevicesChanged();
    void bluetoothDeviceChanged();
    void bluetoothPlaybackStatusChanged();
    void bluetoothMediaControlsAvailableChanged();

    // Signals: metadata / error
    void metaDataChanged();
    void errorOccurred();

private:
    QMediaPlayer *m_mediaPlayer = nullptr;
    QAudioOutput *m_audioOutput = nullptr;

    // Local source state
    QStringList m_playlist;
    int m_currentPlaylistIndex = -1;

    // Radio source state
    bool m_isRadioMode = false;
    QVariantList m_radioStations;
    QString m_currentStationName;
    QString m_currentRadioStationCountry;
    int m_currentStationIndex = -1;
    bool m_radioReconnecting = false;

    // USB source state
    bool m_isUsbMode = false;
    bool m_usbConnected = false;
    QString m_usbRootPath;
    QStringList m_usbTracks;
    int m_currentUsbTrackIndex = -1;

    // Bluetooth source state. BlueZ owns A2DP transport; this class acts as
    // the UI/controller client and uses AVRCP through org.bluez.MediaPlayer1.
    bool m_isBluetoothMode = false;
    bool m_bluetoothAvailable = false;
    bool m_bluetoothScanning = false;
    bool m_bluetoothConnected = false;
    bool m_bluetoothPlaying = false;
    QVariantList m_bluetoothDevices;
    QString m_bluetoothAdapterPath;
    QString m_bluetoothDevicePath;
    QString m_bluetoothDeviceName;
    QString m_bluetoothDeviceAddress;
    QString m_bluetoothMediaPlayerPath;
    QString m_bluetoothMediaControlPath;
    QString m_bluetoothPlaybackStatus = QStringLiteral("stopped");
    qint64 m_bluetoothPosition = 0;
    qint64 m_bluetoothDuration = 0;
    QTimer m_bluetoothRefreshTimer;

    // Metadata / errors
    QString m_audioTitle;
    QString m_audioAuthor;
    QString m_audioAlbum;
    QString m_audioType;
    QString m_errorString;

    void setSource(const QString &audioSource);
    void clearMediaMetaData();
    void previousRadio();
    void nextRadio();
    void setRadioReconnecting(bool reconnecting);
    void setPlaybackError(const QString &message);

    void setBluetoothMode(bool bluetooth_mode);
    void syncBluetoothState(bool report_errors = false);
    void setBluetoothAvailable(bool available);
    void setBluetoothScanning(bool scanning);
    void setBluetoothConnected(bool connected);
    void updateBluetoothDevice(const QString &path,
                               const QString &name,
                               const QString &address);
    void updateBluetoothPlaybackState(const QString &status,
                                      qint64 position,
                                      qint64 duration);
    void sendBluetoothMediaCommand(const QString &command);
    void connectBluetoothPath(const QString &device_path, bool pair_first);
    void clearBluetoothSelection(bool keep_device_list = true);
};

#endif // AUDIOPLAYER_H
