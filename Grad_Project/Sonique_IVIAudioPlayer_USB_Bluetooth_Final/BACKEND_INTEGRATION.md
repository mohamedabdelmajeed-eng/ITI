# Sonique Backend Integration

Sonique now uses the same public `AudioPlayer` API and backend techniques as the Qt6_QML `19.Media_Radio_Player` reference.

## C++ ↔ QML technique

The backend is a `QObject` wrapper around `QMediaPlayer` and `QAudioOutput` and is registered with QML through `QML_ELEMENT`.

```cpp
class AudioPlayer : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    // Q_PROPERTY ...
};
```

`Main.qml` creates the C++ type directly:

```qml
AudioPlayer {
    id: audioPlayerBackend
}
```

No `setContextProperty()` is used.

## Public properties

The public property names match the reference backend:

- `playing`, `position`, `duration`
- `muted`, `volume`
- `playlist`, `currentPlaylistIndex`
- `audioTitle`, `audioAuthor`, `audioAlbum`, `audioType`, `errorString`
- `isRadioMode`, `radioStations`, `currentRadioStationName`, `currentRadioStationCountry`, `radioReconnecting`

## Public methods

The public invokable method names also match the reference:

- `playPause()`
- `stop()`
- `next()`
- `previous()`
- `loadFolder(folder_path)`
- `formatTime(ms)`
- `playRadioStation(index)`
- `addRadioStation(name, url)`

Seeking uses the writable `position` property, exactly through its `setPosition()` setter:

```qml
playbackEngine.position = newPosition
```

## Signals

The wrapper forwards Qt Multimedia changes through its own signals, including `playingStateChanged`, `positionChanged`, `durationChanged`, `muteStateChanged`, `volumeChanged`, `metaDataChanged`, and the radio signals.

## Corrections applied while preserving the API

The Sonique implementation keeps the same public API but corrects several unsafe/incomplete details from the reference implementation: radio index bounds use `>= size`, metadata clearing emits `metaDataChanged()`, station-country changes are notified, `radioReconnecting` follows actual loading/buffering/stalled states, local paths use `QUrl::fromLocalFile()`, more common audio extensions are accepted, and `addRadioStation()` has a working implementation.

## USB backend integration

The USB source now uses the same `QMediaPlayer` and `QAudioOutput` as Local Audio and Radio.

USB backend API exposed to QML:

- `isUsbMode`
- `usbConnected`
- `usbRootPath`
- `usbTracks`
- `currentUsbTrackIndex`
- `loadUsbFolder(folderPath)`
- `useUsbLibrary()`
- `playUsbTrack(index)`
- `clearUsb()`

`SourcePage.qml` uses real USB metadata/state. The folder button opens a USB folder selector, the backend recursively scans supported audio files, and the common Previous / Play-Pause / Next / Stop / Seek / Volume / Mute controls are reused for USB.

The project intentionally does not include a generated `build/` directory or Qt Creator user cache. Open `CMakeLists.txt` in Qt Creator and configure it with a Qt 6.8+ kit so those files are regenerated for the current machine.


## Bluetooth backend integration

The Bluetooth source now uses the same `AudioPlayer` C++/QML wrapper as Local Audio, Radio, and USB. On Linux IVI systems it talks directly to BlueZ through `Qt6::DBus`.

Bluetooth backend API exposed to QML:

- `isBluetoothMode`
- `bluetoothAvailable`
- `bluetoothScanning`
- `bluetoothConnected`
- `bluetoothDevices`
- `bluetoothDeviceName`
- `bluetoothDeviceAddress`
- `bluetoothPlaybackStatus`
- `bluetoothMediaControlsAvailable`
- `useBluetoothSource()`
- `refreshBluetoothDevices()`
- `startBluetoothDiscovery()`
- `stopBluetoothDiscovery()`
- `connectBluetoothDevice(index)`
- `disconnectBluetoothDevice()`

When the Bluetooth source opens, the backend checks BlueZ immediately for an already-connected device. If no device is connected, discovery starts and `SourcePage.qml` opens the Bluetooth device picker. Selecting an unpaired device calls BlueZ `Pair()` first and then `Connect()`; paired devices are connected directly.

Connected-device detection prefers the active A2DP/AVRCP phone over unrelated Bluetooth peripherals. The displayed device name is synchronized from the BlueZ `Alias`/`Name` properties. MAC addresses remain internal identifiers and are never used or shown as user-facing device names; the UI displays a temporary detection label until BlueZ publishes the real name.

For an active phone, AVRCP transport controls and metadata are read from `org.bluez.MediaPlayer1` (with `org.bluez.MediaControl1` as a compatibility fallback). The common `playPause()`, `next()`, `previous()`, and `stop()` methods automatically forward to the Bluetooth phone whenever Bluetooth mode is active. Track title, artist, album, genre, playback status, position, and duration are reflected through the existing public playback/metadata properties.

### Linux audio-stack requirement

The application deliberately does **not** acquire or decode the raw A2DP transport itself. BlueZ exposes connection/control state, while the system audio session (normally PipeWire/WirePlumber or PulseAudio) owns the Bluetooth A2DP transport and routes the phone audio to the IVI speakers. This avoids fighting the system audio daemon for the same transport and matches normal Linux IVI architecture.

The Bluetooth volume slider is therefore disabled in the app's Bluetooth page: the existing `QAudioOutput` volume belongs to `QMediaPlayer` and does not represent the system A2DP sink volume.

## Playback waveform

The waveform in `SourcePage.qml` is shared by Local Audio, Radio, USB, and Bluetooth. Its 40-bar, center-weighted structure uses continuously interpolated travelling waves instead of timer-stepped random motion, producing a smooth premium animation at the display refresh rate. It eases into a clean idle baseline when playback stops. For Qt Multimedia sources it also stops when output is muted or volume is zero; Bluetooth follows AVRCP playback state because A2DP volume belongs to the system audio session.
