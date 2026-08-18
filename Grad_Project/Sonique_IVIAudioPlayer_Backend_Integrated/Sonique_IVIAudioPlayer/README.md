# Sonique IVI Audio — Frontend + C++ Playback Backend

A touch-friendly Qt 6 / QML frontend for an in-vehicle infotainment audio
player. It includes an animated splash screen, a responsive home screen, and a
premium playback page for four media sources:

- Local Media
- Radio
- USB Media
- Bluetooth

The playback icons and album artwork are original SVG assets. They are grouped
inside `assets/` and bundled into the executable through `resources.qrc`.

## Requirements

- Qt 6.8 or later
- CMake 3.16 or later
- A C++17 compiler
- Qt Quick and Qt Quick Controls 2
- Qt Quick Dialogs 2
- Qt Multimedia

## Build and run

Extract the project into a simple path without parentheses, for example
`~/QtProjects/Sonique_IVIAudioPlayer`. Parentheses in the source or build path
can be interpreted by the shell while Qt generates the resource source file.

```bash
cmake -S . -B build
cmake --build build -j
./build/appIVIAudioPlayer
```

You can also open `CMakeLists.txt` directly in Qt Creator, select a Desktop Qt
6 kit, then press **Run**.

## Current behavior

1. The application opens with a three-second animated Sonique splash screen.
2. It transitions to the IVI source-selection home page.
3. Pressing a source card opens the matching dynamic playback page.
4. The title, source icon, track information, quality, and connection badge
   adapt to Local Media, Radio, USB, or Bluetooth.
5. Local Media opens a native folder chooser. Supported files are MP3, WAV,
   M4A, AAC, FLAC, and OGG.
6. Radio starts the first built-in internet station. Previous and next move
   through the station catalog.
7. Progress, seeking, play/pause, previous, next, stop, mute, and volume are
   connected to Qt Multimedia through the C++ backend.
8. Track metadata, duration, position, station information, buffering state,
   and playback errors flow from C++ to QML.
9. The back button returns to the home page using an animated transition.

## Backend naming

The backend intentionally uses names different from the supplied AudioPlayer
example. Its class is `SoniquePlaybackEngine`, and it is exposed to QML as
`soniquePlaybackEngine`. Examples include:

- `playing` became `playbackActive`
- `position` became `playheadMs`
- `duration` became `mediaLengthMs`
- `muted` became `silenceEnabled`
- `volume` became `outputLevel`
- `playlist` became `localTracks`
- `playPause()` became `togglePlayback()`
- `loadFolder()` became `loadLocalFolder()`
- `playRadioStation()` became `tuneStation()`

USB detection and Bluetooth streaming remain visual frontend placeholders.
