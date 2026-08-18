import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Item {
    id: root

    property string sourceId: "local"
    property string pageTitle: qsTr("Local Media")
    property string iconText: "♪"
    property color accentColor: "#D9A95B"

    required property var playbackEngine

    // Playback values received from the C++ backend.
    readonly property bool playing: playbackEngine.playbackActive
    readonly property bool muted: playbackEngine.silenceEnabled

    readonly property bool backendSupported:
        sourceId === "local" || sourceId === "radio"

    readonly property real trackProgress:
        playbackEngine.mediaLengthMs > 0
        ? playbackEngine.playheadMs / playbackEngine.mediaLengthMs
        : 0

    readonly property real volumeLevel: playbackEngine.outputLevel

    // Theme colors.
    readonly property color backgroundColor: "#030A12"
    readonly property color panelColor: "#09121C"
    readonly property color primaryText: "#F5F7FA"
    readonly property color secondaryText: "#91A0AE"
    readonly property color gold: "#E8B864"
    readonly property color cyan: "#28D9F2"

    readonly property real albumSize:
        Math.min(286, Math.max(230, height * 0.40))

    readonly property var mediaInfo: infoForSource(sourceId)

    readonly property int elapsedMs:
        mediaInfo.live ? 0 : playbackEngine.playheadMs

    signal backRequested()

    function infoForSource(id) {
        switch (id) {
        case "radio":
            return {
                "title": playbackEngine.trackTitle
                         || playbackEngine.tunedStationName
                         || qsTr("Radio"),

                "artist": playbackEngine.trackArtist
                          || playbackEngine.tunedStationCountry
                          || qsTr("Internet Radio"),

                "album": playbackEngine.trackAlbum
                         || qsTr("Live Stream"),

                "genre": playbackEngine.trackGenre
                         || qsTr("Radio"),

                "quality": playbackEngine.streamBuffering
                           ? qsTr("BUFFERING")
                           : qsTr("ONLINE STREAM"),

                "status": playbackEngine.streamBuffering
                          ? qsTr("CONNECTING")
                          : qsTr("LIVE SIGNAL"),

                "durationMs": 0,
                "live": true
            }

        case "usb":
            return {
                "title": qsTr("Courses"),
                "artist": qsTr("ITI"),
                "album": qsTr("Open Roads"),
                "genre": qsTr("Alternative Electronic"),
                "quality": qsTr("WAV · 24-bit"),
                "status": qsTr("USB CONNECTED"),
                "durationMs": 252000,
                "live": false
            }

        case "bluetooth":
            return {
                "title": qsTr("SPOTIFY"),
                "artist": qsTr("MMM"),
                "album": qsTr("City Lights"),
                "genre": qsTr("Dream Pop"),
                "quality": qsTr("AAC · High Quality"),
                "status": qsTr("PHONE CONNECTED"),
                "durationMs": 231000,
                "live": false
            }

        default:
            return {
                "title": playbackEngine.trackTitle
                         || qsTr("Choose an audio folder"),

                "artist": playbackEngine.trackArtist
                          || qsTr("Unknown author"),

                "album": playbackEngine.trackAlbum
                         || qsTr("Local library"),

                "genre": playbackEngine.trackGenre
                         || qsTr("Audio"),

                "quality": qsTr("LOCAL FILE"),

                "status": playbackEngine.localTracks.length > 0
                          ? qsTr("ON DEVICE")
                          : qsTr("CHOOSE FOLDER"),

                "durationMs": playbackEngine.mediaLengthMs,
                "live": false
            }
        }
    }

    function sourceIcon() {
        switch (sourceId) {
        case "radio":
            return "qrc:/assets/icons/radio.svg"

        case "usb":
            return "qrc:/assets/icons/usb.svg"

        case "bluetooth":
            return "qrc:/assets/icons/bluetooth.svg"

        default:
            return "qrc:/assets/icons/local-audio.svg"
        }
    }

    Component.onCompleted: {
        if (sourceId === "radio"
                && playbackEngine.stationCatalog.length > 0) {
            playbackEngine.tuneStation(0)
        } else if (sourceId === "local") {
            playbackEngine.useLocalLibrary()
        }
    }

    FolderDialog {
        id: audioFolderDialog

        title: qsTr("Choose an audio folder")

        currentFolder: StandardPaths.standardLocations(
                           StandardPaths.MusicLocation)[0]

        options: FolderDialog.DontUseNativeDialog
                 | FolderDialog.DontResolveSymlinks
                 | FolderDialog.ReadOnly

        onAccepted: {
            playbackEngine.loadLocalFolder(selectedFolder)
        }
    }

    component IconButton: Item {
        id: iconButton

        property url iconSource
        property string label
        property int buttonSize: 64
        property int iconSize: 25
        property bool prominent: false
        property bool selected: false
        property color highlightColor: root.gold

        signal clicked()

        width: buttonSize
        height: buttonSize
        scale: buttonMouse.pressed ? 0.94 : 1.0

        Behavior on scale {
            NumberAnimation {
                duration: 110
                easing.type: Easing.OutCubic
            }
        }

        Rectangle {
            anchors.centerIn: parent

            width: parent.width + 14
            height: parent.height + 14
            radius: width / 2

            color: "transparent"

            border.width: iconButton.prominent ? 2 : 0
            border.color: iconButton.highlightColor

            opacity: iconButton.prominent
                     ? (buttonMouse.containsMouse ? 0.38 : 0.22)
                     : 0
        }

        Rectangle {
            anchors.fill: parent

            radius: width / 2

            color: buttonMouse.pressed
                   ? "#18212B"
                   : (buttonMouse.containsMouse || iconButton.selected
                      ? "#151D26"
                      : "#101720")

            border.width: iconButton.prominent ? 2 : 1

            border.color: iconButton.prominent
                          ? iconButton.highlightColor
                          : (buttonMouse.containsMouse
                             ? "#74808B"
                             : "#44505D")

            Rectangle {
                anchors.fill: parent
                anchors.margins: iconButton.prominent ? 5 : 1

                radius: width / 2
                color: "transparent"

                border.width: iconButton.prominent ? 1 : 0
                border.color: "#FFF1CC"

                opacity: 0.35
            }
        }

        Image {
            anchors.centerIn: parent

            width: iconButton.iconSize
            height: iconButton.iconSize

            source: iconButton.iconSource
            fillMode: Image.PreserveAspectFit
            mipmap: true

            opacity: buttonMouse.containsMouse ? 1.0 : 0.92
        }

        MouseArea {
            id: buttonMouse

            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: iconButton.clicked()
        }

        ToolTip.visible:
            buttonMouse.containsMouse && iconButton.label.length > 0

        ToolTip.text: iconButton.label
        ToolTip.delay: 500
    }

    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#020711"
            }

            GradientStop {
                position: 0.58
                color: root.backgroundColor
            }

            GradientStop {
                position: 1.0
                color: "#07111B"
            }
        }
    }

    Rectangle {
        width: 560
        height: 560
        radius: width / 2

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: -260
        anchors.topMargin: -340

        color: root.cyan
        opacity: 0.035
    }

    Rectangle {
        width: 500
        height: 500
        radius: width / 2

        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: -320
        anchors.bottomMargin: -350

        color: root.gold
        opacity: 0.035
    }

    ColumnLayout {
        anchors.fill: parent

        anchors.leftMargin: Math.max(34, root.width * 0.045)
        anchors.rightMargin: Math.max(34, root.width * 0.045)
        anchors.topMargin: 22
        anchors.bottomMargin: 22

        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 48

            spacing: 12

            IconButton {
                buttonSize: 42
                iconSize: 18

                iconSource: "qrc:/assets/icons/back.svg"
                label: qsTr("Back")

                onClicked: root.backRequested()
            }

            Image {
                Layout.preferredWidth: 24
                Layout.preferredHeight: 24

                source: root.sourceIcon()
                fillMode: Image.PreserveAspectFit
                mipmap: true
            }

            Text {
                text: root.pageTitle
                color: root.primaryText

                font.pixelSize: 20
                font.weight: Font.DemiBold
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                Layout.preferredWidth: sourceStatus.implicitWidth + 30
                Layout.preferredHeight: 32

                radius: 16
                color: "#0C1822"

                border.width: 1
                border.color: "#203242"

                Row {
                    anchors.centerIn: parent
                    spacing: 8

                    Rectangle {
                        width: 7
                        height: 7
                        radius: 4

                        anchors.verticalCenter: parent.verticalCenter

                        color: root.sourceId === "radio"
                               ? "#FF785A"
                               : "#54E7B0"
                    }

                    Text {
                        id: sourceStatus

                        text: root.mediaInfo.status
                        color: root.secondaryText

                        font.pixelSize: 9
                        font.weight: Font.DemiBold
                        font.letterSpacing: 1.1
                    }
                }
            }
        }

        Item {
            Layout.preferredHeight: 16
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: root.albumSize

            spacing: Math.max(28, root.width * 0.042)

            Rectangle {
                Layout.preferredWidth: root.albumSize
                Layout.preferredHeight: root.albumSize
                Layout.alignment: Qt.AlignVCenter

                radius: 28
                color: "#0B1724"

                border.width: 1
                border.color: "#44505B"

                clip: true

                Image {
                    anchors.fill: parent

                    source: "qrc:/assets/images/midnight-drive.svg"
                    fillMode: Image.PreserveAspectCrop
                    mipmap: true
                }

                Rectangle {
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.margins: 14

                    width: coverSourceRow.implicitWidth + 22
                    height: 32
                    radius: 16

                    color: "#BF06101B"

                    border.width: 1
                    border.color: "#594D6D83"

                    Row {
                        id: coverSourceRow

                        anchors.centerIn: parent
                        spacing: 7

                        Image {
                            width: 15
                            height: 15

                            anchors.verticalCenter: parent.verticalCenter

                            source: root.sourceIcon()
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            text: root.pageTitle.toUpperCase()
                            color: "#E8EFF4"

                            font.pixelSize: 8
                            font.weight: Font.DemiBold
                            font.letterSpacing: 1
                        }
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                spacing: 0

                Text {
                    Layout.fillWidth: true

                    text: root.mediaInfo.title
                    color: root.primaryText

                    font.pixelSize: root.width < 1050 ? 30 : 36
                    font.weight: Font.Bold

                    elide: Text.ElideRight
                }

                Item {
                    Layout.preferredHeight: 10
                }

                GridLayout {
                    columns: 2
                    columnSpacing: 16
                    rowSpacing: 6

                    Text {
                        text: qsTr("Author:")
                        color: root.gold

                        font.pixelSize: 15
                        font.weight: Font.Medium
                    }

                    Text {
                        text: root.mediaInfo.artist
                        color: root.primaryText

                        font.pixelSize: 15
                    }

                    Text {
                        text: qsTr("Album:")
                        color: root.gold

                        font.pixelSize: 15
                        font.weight: Font.Medium
                    }

                    Text {
                        text: root.mediaInfo.album
                        color: root.primaryText

                        font.pixelSize: 15
                    }

                    Text {
                        text: qsTr("Genre:")
                        color: root.gold

                        font.pixelSize: 15
                        font.weight: Font.Medium
                    }

                    Text {
                        text: root.mediaInfo.genre
                        color: root.primaryText

                        font.pixelSize: 15
                    }

                    Text {
                        text: qsTr("Quality:")
                        color: root.gold

                        font.pixelSize: 15
                        font.weight: Font.Medium
                    }

                    Text {
                        text: root.mediaInfo.quality
                        color: root.primaryText

                        font.pixelSize: 15
                    }
                }

                Item {
                    id: waveform

                    property var amplitudes: [
                        0.10, 0.15, 0.18, 0.24,
                        0.16, 0.28, 0.20, 0.38,
                        0.55, 0.82, 0.50, 0.30,
                        0.19, 0.32, 0.45, 0.30,
                        0.62, 0.90, 0.64, 0.48,
                        0.28, 0.20, 0.16, 0.40,
                        0.70, 0.43, 0.30, 0.24,
                        0.18, 0.15, 0.12, 0.10
                    ]

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.topMargin: 10
                    Layout.minimumHeight: 68

                    Rectangle {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter

                        height: 1
                        color: "#173249"
                    }

                    Row {
                        id: waveRow

                        anchors.fill: parent
                        spacing: 4

                        Repeater {
                            model: waveform.amplitudes

                            Rectangle {
                                required property real modelData

                                width: Math.max(
                                           3,
                                           (waveRow.width
                                            - (waveform.amplitudes.length - 1)
                                            * waveRow.spacing)
                                           / waveform.amplitudes.length
                                       )

                                height: Math.max(
                                            6,
                                            waveRow.height * modelData
                                        )

                                y: (waveRow.height - height) / 2

                                radius: width / 2

                                gradient: Gradient {
                                    GradientStop {
                                        position: 0.0
                                        color: root.cyan
                                    }

                                    GradientStop {
                                        position: 0.65
                                        color: "#13AEDD"
                                    }

                                    GradientStop {
                                        position: 1.0
                                        color: "#08639D"
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.minimumHeight: 14
            Layout.maximumHeight: 70
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 32

            spacing: 14

            Text {
                Layout.preferredWidth: 46

                text: root.mediaInfo.live
                      ? qsTr("LIVE")
                      : playbackEngine.formatClock(root.elapsedMs)

                color: root.primaryText
                font.pixelSize: 14
                horizontalAlignment: Text.AlignLeft
            }

            Slider {
                id: progressSlider

                Layout.fillWidth: true

                from: 0
                to: 1

                value: root.mediaInfo.live
                       ? 1
                       : root.trackProgress

                enabled: root.backendSupported
                         && !root.mediaInfo.live
                         && playbackEngine.mediaLengthMs > 0

                onMoved: {
                    playbackEngine.seekTo(
                        Math.round(
                            value * playbackEngine.mediaLengthMs
                        )
                    )
                }

                background: Rectangle {
                    x: progressSlider.leftPadding

                    y: progressSlider.topPadding
                       + progressSlider.availableHeight / 2
                       - height / 2

                    width: progressSlider.availableWidth
                    height: 5
                    radius: 3

                    color: "#34414E"

                    Rectangle {
                        width: progressSlider.visualPosition
                               * parent.width

                        height: parent.height
                        radius: parent.radius
                        color: root.gold
                    }
                }

                handle: Rectangle {
                    x: progressSlider.leftPadding
                       + progressSlider.visualPosition
                       * (progressSlider.availableWidth - width)

                    y: progressSlider.topPadding
                       + progressSlider.availableHeight / 2
                       - height / 2

                    implicitWidth: 18
                    implicitHeight: 18
                    radius: 9

                    color: "#FFE6B2"

                    border.width: 1
                    border.color: "#FFF4D9"

                    opacity: root.mediaInfo.live ? 0 : 1
                }
            }

            Text {
                Layout.preferredWidth: 46

                text: root.mediaInfo.live
                      ? "—"
                      : playbackEngine.formatClock(
                            root.mediaInfo.durationMs
                        )

                color: root.primaryText
                font.pixelSize: 14
                horizontalAlignment: Text.AlignRight
            }
        }

        Item {
            Layout.preferredHeight: 10
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 92

            spacing: 26

            Item {
                Layout.fillWidth: true
            }

            IconButton {
                buttonSize: 50
                iconSize: 21

                iconSource: "qrc:/assets/icons/folder.svg"
                label: qsTr("Open library")

                selected: audioFolderDialog.visible
                highlightColor: root.cyan

                enabled: root.sourceId === "local"
                opacity: enabled ? 1.0 : 0.35

                onClicked: audioFolderDialog.open()
            }

            IconButton {
                buttonSize: 66
                iconSize: 27

                iconSource: "qrc:/assets/icons/previous.svg"
                label: qsTr("Previous")

                enabled: root.backendSupported
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.playPrevious()
            }

            IconButton {
                buttonSize: 80
                iconSize: root.playing ? 28 : 31

                prominent: true

                iconSource: root.playing
                            ? "qrc:/assets/icons/pause.svg"
                            : "qrc:/assets/icons/play.svg"

                label: root.playing
                       ? qsTr("Pause")
                       : qsTr("Play")

                enabled: root.backendSupported
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.togglePlayback()
            }

            IconButton {
                buttonSize: 66
                iconSize: 27

                iconSource: "qrc:/assets/icons/next.svg"
                label: qsTr("Next")

                enabled: root.backendSupported
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.playNext()
            }

            IconButton {
                buttonSize: 50
                iconSize: 19

                iconSource: "qrc:/assets/icons/stop.svg"
                label: qsTr("Stop")

                enabled: root.backendSupported
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.stopPlayback()
            }

            Item {
                Layout.fillWidth: true
            }
        }

        Item {
            Layout.preferredHeight: 4
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            spacing: 18

            Item {
                Layout.fillWidth: true
            }

            IconButton {
                buttonSize: 46
                iconSize: 22

                iconSource: root.muted || root.volumeLevel === 0
                            ? "qrc:/assets/icons/volume-muted.svg"
                            : "qrc:/assets/icons/volume-high.svg"

                label: root.muted
                       ? qsTr("Unmute")
                       : qsTr("Mute")

                selected: root.muted
                highlightColor: root.cyan

                enabled: root.backendSupported
                opacity: enabled ? 1.0 : 0.35

                onClicked: {
                    playbackEngine.silenceEnabled =
                        !playbackEngine.silenceEnabled
                }
            }

            Slider {
                id: volumeSlider

                Layout.preferredWidth:
                    Math.min(610, root.width * 0.52)

                from: 0
                to: 1

                value: root.volumeLevel

                enabled: root.backendSupported
                opacity: enabled ? 1.0 : 0.35

                onMoved: {
                    playbackEngine.outputLevel = value
                    playbackEngine.silenceEnabled = false
                }

                background: Rectangle {
                    x: volumeSlider.leftPadding

                    y: volumeSlider.topPadding
                       + volumeSlider.availableHeight / 2
                       - height / 2

                    width: volumeSlider.availableWidth
                    height: 7
                    radius: 4

                    gradient: Gradient {
                        orientation: Gradient.Horizontal

                        GradientStop {
                            position: 0.0
                            color: root.cyan
                        }

                        GradientStop {
                            position: 0.72
                            color: "#77D7D5"
                        }

                        GradientStop {
                            position: 1.0
                            color: root.gold
                        }
                    }

                    Rectangle {
                        x: volumeSlider.visualPosition
                           * parent.width

                        width: parent.width - x
                        height: parent.height
                        radius: parent.radius

                        color: "#34414E"
                        opacity: 0.72
                    }
                }

                handle: Rectangle {
                    x: volumeSlider.leftPadding
                       + volumeSlider.visualPosition
                       * (volumeSlider.availableWidth - width)

                    y: volumeSlider.topPadding
                       + volumeSlider.availableHeight / 2
                       - height / 2

                    implicitWidth: 22
                    implicitHeight: 22
                    radius: 11

                    color: "#14202A"

                    border.width: 2
                    border.color: root.gold

                    Rectangle {
                        anchors.centerIn: parent

                        width: 8
                        height: 8
                        radius: 4

                        color: "#FFE3A7"
                    }
                }
            }

            Text {
                Layout.preferredWidth: 58

                text: root.muted
                      ? qsTr("Muted")
                      : Math.round(root.volumeLevel * 100) + "%"

                color: root.primaryText
                font.pixelSize: 15
                horizontalAlignment: Text.AlignRight
            }

            Item {
                Layout.fillWidth: true
            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: 40
        anchors.rightMargin: 40
        anchors.bottomMargin: 12

        height: playbackErrorText.implicitHeight + 20
        radius: 10

        color: "#D92B1820"

        border.width: 1
        border.color: "#FF785A"

        visible: playbackEngine.lastPlaybackError.length > 0

        Text {
            id: playbackErrorText

            anchors.centerIn: parent

            width: parent.width - 24

            text: playbackEngine.lastPlaybackError
            color: "#FFE6DF"

            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
        }
    }
}