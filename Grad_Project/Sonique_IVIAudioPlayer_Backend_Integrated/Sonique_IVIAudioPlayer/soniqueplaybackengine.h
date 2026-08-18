#ifndef SONIQUEPLAYBACKENGINE_H
#define SONIQUEPLAYBACKENGINE_H

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include <QStringList>
#include <QUrl>
#include <QVariantList>

class SoniquePlaybackEngine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool playbackActive READ isPlaybackActive NOTIFY playbackActiveChanged FINAL)
    Q_PROPERTY(qint64 playheadMs READ playhead NOTIFY playheadChanged FINAL)
    Q_PROPERTY(qint64 mediaLengthMs READ mediaLength NOTIFY mediaLengthChanged FINAL)

    Q_PROPERTY(bool silenceEnabled READ isSilenced WRITE setSilenced
                   NOTIFY silenceEnabledChanged FINAL)
    Q_PROPERTY(float outputLevel READ outputLevel WRITE setOutputLevel
                   NOTIFY outputLevelChanged FINAL)

    Q_PROPERTY(QStringList localTracks READ localTracks NOTIFY localTracksChanged FINAL)
    Q_PROPERTY(int selectedTrackIndex READ selectedTrackIndex
                   NOTIFY selectedTrackIndexChanged FINAL)

    Q_PROPERTY(QString trackTitle READ trackTitle NOTIFY trackDetailsChanged FINAL)
    Q_PROPERTY(QString trackArtist READ trackArtist NOTIFY trackDetailsChanged FINAL)
    Q_PROPERTY(QString trackAlbum READ trackAlbum NOTIFY trackDetailsChanged FINAL)
    Q_PROPERTY(QString trackGenre READ trackGenre NOTIFY trackDetailsChanged FINAL)
    Q_PROPERTY(QString lastPlaybackError READ lastPlaybackError
                   NOTIFY playbackErrorChanged FINAL)

    Q_PROPERTY(bool radioActive READ isRadioActive NOTIFY radioActiveChanged FINAL)
    Q_PROPERTY(QVariantList stationCatalog READ stationCatalog
                   NOTIFY stationCatalogChanged FINAL)
    Q_PROPERTY(QString tunedStationName READ tunedStationName
                   NOTIFY tunedStationChanged FINAL)
    Q_PROPERTY(QString tunedStationCountry READ tunedStationCountry
                   NOTIFY tunedStationChanged FINAL)
    Q_PROPERTY(bool streamBuffering READ isStreamBuffering
                   NOTIFY streamBufferingChanged FINAL)

public:
    explicit SoniquePlaybackEngine(QObject *parent = nullptr);

    bool isPlaybackActive() const;
    qint64 playhead() const;
    qint64 mediaLength() const;
    bool isSilenced() const;
    float outputLevel() const;
    QStringList localTracks() const;
    int selectedTrackIndex() const;
    QString trackTitle() const;
    QString trackArtist() const;
    QString trackAlbum() const;
    QString trackGenre() const;
    QString lastPlaybackError() const;
    bool isRadioActive() const;
    QVariantList stationCatalog() const;
    QString tunedStationName() const;
    QString tunedStationCountry() const;
    bool isStreamBuffering() const;

    void setSilenced(bool enabled);
    void setOutputLevel(float level);

    Q_INVOKABLE void togglePlayback();
    Q_INVOKABLE void stopPlayback();
    Q_INVOKABLE void playNext();
    Q_INVOKABLE void playPrevious();
    Q_INVOKABLE void seekTo(qint64 milliseconds);
    Q_INVOKABLE void loadLocalFolder(const QUrl &folderUrl);
    Q_INVOKABLE void useLocalLibrary();
    Q_INVOKABLE QString formatClock(qint64 milliseconds) const;
    Q_INVOKABLE void tuneStation(int stationIndex);
    Q_INVOKABLE void saveStation(const QString &name,
                                 const QString &country,
                                 const QUrl &streamUrl);

signals:
    void playbackActiveChanged();
    void playheadChanged();
    void mediaLengthChanged();
    void silenceEnabledChanged();
    void outputLevelChanged();
    void localTracksChanged();
    void selectedTrackIndexChanged();
    void trackDetailsChanged();
    void playbackErrorChanged();
    void radioActiveChanged();
    void stationCatalogChanged();
    void tunedStationChanged();
    void streamBufferingChanged();

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;

    QStringList m_localTracks;
    int m_selectedTrackIndex = -1;

    QString m_trackTitle;
    QString m_trackArtist;
    QString m_trackAlbum;
    QString m_trackGenre;
    QString m_lastPlaybackError;

    bool m_radioActive = false;
    QVariantList m_stationCatalog;
    int m_tunedStationIndex = -1;
    QString m_tunedStationName;
    QString m_tunedStationCountry;
    bool m_streamBuffering = false;

    void openMedia(const QUrl &source);
    void clearTrackDetails();
    void setRadioActive(bool enabled);
    void setStreamBuffering(bool buffering);
    void reportError(const QString &message);
};

#endif // SONIQUEPLAYBACKENGINE_H
