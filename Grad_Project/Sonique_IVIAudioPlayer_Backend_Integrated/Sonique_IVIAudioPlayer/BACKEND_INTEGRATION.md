# Backend integration map

The original frontend changed only local QML properties. The integrated app
owns one `SoniquePlaybackEngine` object in `main.cpp` and exposes it to QML as
`soniquePlaybackEngine`. `Main.qml` gives that object to every `SourcePage`.

## Renamed API

| Supplied AudioPlayer name | Integrated Sonique name |
| --- | --- |
| `AudioPlayer` | `SoniquePlaybackEngine` |
| `playing` | `playbackActive` |
| `getPlayingState()` | `isPlaybackActive()` |
| `playingStateChanged()` | `playbackActiveChanged()` |
| `position` | `playheadMs` |
| `getPosition()` | `playhead()` |
| `positionChanged()` | `playheadChanged()` |
| `duration` | `mediaLengthMs` |
| `getDuration()` | `mediaLength()` |
| `durationChanged()` | `mediaLengthChanged()` |
| `muted` | `silenceEnabled` |
| `getMuteState()` | `isSilenced()` |
| `setMuteState()` | `setSilenced()` |
| `muteStateChanged()` | `silenceEnabledChanged()` |
| `volume` | `outputLevel` |
| `getVolume()` | `outputLevel()` |
| `setVolume()` | `setOutputLevel()` |
| `volumeChanged()` | `outputLevelChanged()` |
| `playlist` | `localTracks` |
| `currentPlaylistIndex` | `selectedTrackIndex` |
| `audioTitle` | `trackTitle` |
| `audioAuthor` | `trackArtist` |
| `audioAlbum` | `trackAlbum` |
| `audioType` | `trackGenre` |
| `errorString` | `lastPlaybackError` |
| `isRadioMode` | `radioActive` |
| `radioStations` | `stationCatalog` |
| `currentRadioStationName` | `tunedStationName` |
| `currentRadioStationCountry` | `tunedStationCountry` |
| `radioReconnecting` | `streamBuffering` |
| `playPause()` | `togglePlayback()` |
| `stop()` | `stopPlayback()` |
| `next()` | `playNext()` |
| `previous()` | `playPrevious()` |
| `setPosition()` | `seekTo()` |
| `loadFolder()` | `loadLocalFolder()` |
| `formatTime()` | `formatClock()` |
| `playRadioStation()` | `tuneStation()` |
| `addRadioStation()` | `saveStation()` |

## Data flow

1. The user presses a QML control.
2. `SourcePage.qml` calls a method or changes a writable property on
   `SoniquePlaybackEngine`.
3. The backend controls `QMediaPlayer` or `QAudioOutput`.
4. Qt emits a playback signal.
5. The backend forwards it using a renamed Sonique signal.
6. QML automatically reads the changed property and redraws the screen.

## Important fixes made during integration

- The radio index check now rejects `index == station count`, preventing an
  out-of-range access.
- Metadata clearing emits `trackDetailsChanged()` instead of incorrectly trying
  to emit the `QMediaMetaData` type.
- Local paths use `QUrl::fromLocalFile()`.
- `saveStation()` is implemented and validates its input.
- Folder scanning accepts MP3, WAV, M4A, AAC, FLAC, OGG, and sorts by name.
- Playback errors are displayed in the QML page.

## Build note

Open `CMakeLists.txt` in Qt Creator with a Qt 6.8 or newer Desktop kit. The kit
must include Qt Multimedia and Qt Quick Dialogs. Use a fresh build directory;
do not reuse the old frontend-only build directory.
