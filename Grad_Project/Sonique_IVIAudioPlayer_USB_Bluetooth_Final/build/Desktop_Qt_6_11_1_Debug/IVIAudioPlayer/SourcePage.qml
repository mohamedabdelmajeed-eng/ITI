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
    readonly property bool playing: playbackEngine.playing
    readonly property bool muted: playbackEngine.muted

    // All source cards use the same C++ AudioPlayer backend.
    readonly property bool backendSupported:
        sourceId === "local"
        || sourceId === "radio"
        || sourceId === "usb"
        || sourceId === "bluetooth"

    // Playback buttons become active only when the selected source has media.
    readonly property bool playbackAvailable:
        sourceId === "radio"
        ? playbackEngine.radioStations.length > 0
        : (sourceId === "usb"
           ? playbackEngine.usbTracks.length > 0
           : (sourceId === "bluetooth"
              ? playbackEngine.bluetoothConnected
                && playbackEngine.bluetoothMediaControlsAvailable
              : (sourceId === "local"
                 ? playbackEngine.playlist.length > 0
                 : false)))

    readonly property real trackProgress:
        playbackEngine.duration > 0
        ? playbackEngine.position / playbackEngine.duration
        : 0

    readonly property real volumeLevel: playbackEngine.volume

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
        mediaInfo.live ? 0 : playbackEngine.position

    signal backRequested()

    function fileNameFromPath(path) {
        var value = String(path)
        var parts = value.split("/")
        var name = parts.length > 0 ? parts[parts.length - 1] : value
        return name.length > 0 ? name : qsTr("USB Track")
    }

    function currentUsbFileName() {
        if (playbackEngine.usbTracks.length === 0)
            return ""

        var index = playbackEngine.currentUsbTrackIndex
        if (index < 0 || index >= playbackEngine.usbTracks.length)
            index = 0

        return fileNameFromPath(playbackEngine.usbTracks[index])
    }

    function isBluetoothMacAddress(value) {
        return /^([0-9A-F]{2}[:-]){5}[0-9A-F]{2}$/i.test(
                    String(value || "").trim())
    }

    function bluetoothDisplayName(deviceInfo) {
        var name = String(deviceInfo && deviceInfo.name
                          ? deviceInfo.name : "").trim()
        if (name.length === 0 || isBluetoothMacAddress(name))
            return qsTr("Detecting device name…")
        return name
    }

    function infoForSource(id) {
        switch (id) {
        case "radio":
            return {
                "title": playbackEngine.audioTitle
                         || playbackEngine.currentRadioStationName
                         || qsTr("Radio"),

                "artist": playbackEngine.audioAuthor
                          || playbackEngine.currentRadioStationCountry
                          || qsTr("Internet Radio"),

                "album": playbackEngine.audioAlbum
                         || qsTr("Live Stream"),

                "genre": playbackEngine.audioType
                         || qsTr("Radio"),

                "quality": playbackEngine.radioReconnecting
                           ? qsTr("BUFFERING")
                           : qsTr("ONLINE STREAM"),

                "status": playbackEngine.radioReconnecting
                          ? qsTr("CONNECTING")
                          : qsTr("LIVE SIGNAL"),

                "durationMs": 0,
                "live": true
            }

        case "usb":
            return {
                "title": playbackEngine.audioTitle
                         || root.currentUsbFileName()
                         || qsTr("Choose USB media"),

                "artist": playbackEngine.audioAuthor
                          || qsTr("Unknown author"),

                "album": playbackEngine.audioAlbum
                         || qsTr("USB library"),

                "genre": playbackEngine.audioType
                         || qsTr("Audio"),

                "quality": qsTr("USB FILE"),

                "status": !playbackEngine.usbConnected
                          ? qsTr("CHOOSE USB")
                          : (playbackEngine.usbTracks.length > 0
                             ? qsTr("USB CONNECTED")
                             : qsTr("NO AUDIO FILES")),

                "durationMs": playbackEngine.duration,
                "live": false
            }

        case "bluetooth":
            return {
                // Keep the connected phone name visible even while AVRCP is
                // publishing track metadata.
                "title": playbackEngine.bluetoothConnected
                         ? root.bluetoothDisplayName({
                               "name": playbackEngine.bluetoothDeviceName
                           })
                         : qsTr("Bluetooth Audio"),

                "artist": playbackEngine.audioTitle
                          || playbackEngine.audioAuthor
                          || (playbackEngine.bluetoothConnected
                              ? qsTr("Phone audio")
                              : qsTr("Choose a phone")),

                "album": playbackEngine.audioAlbum
                         || qsTr("Wireless audio"),

                "genre": playbackEngine.audioType
                         || qsTr("Bluetooth"),

                "quality": playbackEngine.bluetoothConnected
                           ? qsTr("BLUETOOTH · A2DP")
                           : qsTr("BLUETOOTH"),

                "status": !playbackEngine.bluetoothAvailable
                          ? qsTr("BLUETOOTH OFF")
                          : (!playbackEngine.bluetoothConnected
                             ? (playbackEngine.bluetoothScanning
                                ? qsTr("SCANNING")
                                : qsTr("CHOOSE DEVICE"))
                             : (playbackEngine.bluetoothMediaControlsAvailable
                                ? qsTr("PHONE CONNECTED")
                                : qsTr("CONNECTED · OPEN MEDIA"))),

                "durationMs": playbackEngine.duration,
                "live": false
            }

        default:
            return {
                "title": playbackEngine.audioTitle
                         || qsTr("Choose an audio folder"),

                "artist": playbackEngine.audioAuthor
                          || qsTr("Unknown author"),

                "album": playbackEngine.audioAlbum
                         || qsTr("Local library"),

                "genre": playbackEngine.audioType
                         || qsTr("Audio"),

                "quality": qsTr("LOCAL FILE"),

                "status": playbackEngine.playlist.length > 0
                          ? qsTr("ON DEVICE")
                          : qsTr("CHOOSE FOLDER"),

                "durationMs": playbackEngine.duration,
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
                && playbackEngine.radioStations.length > 0) {
            playbackEngine.playRadioStation(0)

        } else if (sourceId === "local") {
            // Reactivate the existing local library without starting playback.
            playbackEngine.useLocalLibrary()

        } else if (sourceId === "usb") {
            // Reactivate the existing USB library if it was already selected.
            playbackEngine.useUsbLibrary()

            if (!playbackEngine.usbConnected)
                usbFolderDialog.open()

        } else if (sourceId === "bluetooth") {
            // Detect an already-connected phone immediately. If none exists,
            // the backend starts BlueZ discovery and the device picker opens.
            playbackEngine.useBluetoothSource()

            if (!playbackEngine.bluetoothConnected)
                bluetoothDeviceDialog.open()
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
            playbackEngine.loadFolder(selectedFolder.toString())
        }
    }

    FolderDialog {
        id: usbFolderDialog

        title: qsTr("Choose USB drive or USB music folder")

        options: FolderDialog.DontUseNativeDialog
                 | FolderDialog.DontResolveSymlinks
                 | FolderDialog.ReadOnly

        onAccepted: {
            playbackEngine.loadUsbFolder(selectedFolder.toString())
        }
    }

    Dialog {
        id: bluetoothDeviceDialog

        parent: Overlay.overlay
        anchors.centerIn: parent
        modal: true
        focus: true

        width: Math.min(620, root.width - 80)
        height: Math.min(500, root.height - 90)

        title: qsTr("Bluetooth devices")
        standardButtons: Dialog.Close

        onOpened: {
            playbackEngine.refreshBluetoothDevices()
            if (!playbackEngine.bluetoothConnected
                    && !playbackEngine.bluetoothScanning)
                playbackEngine.startBluetoothDiscovery()
        }

        onClosed: playbackEngine.stopBluetoothDiscovery()

        background: Rectangle {
            radius: 18
            color: "#0A141F"
            border.width: 1
            border.color: "#294052"
        }

        contentItem: ColumnLayout {
            spacing: 12

            RowLayout {
                Layout.fillWidth: true

                Text {
                    Layout.fillWidth: true
                    text: !playbackEngine.bluetoothAvailable
                          ? qsTr("Bluetooth adapter unavailable")
                          : (playbackEngine.bluetoothScanning
                             ? qsTr("Scanning for nearby devices…")
                             : qsTr("Select a device to pair or connect"))
                    color: root.secondaryText
                    font.pixelSize: 13
                }

                Button {
                    text: playbackEngine.bluetoothScanning
                          ? qsTr("Refresh")
                          : qsTr("Scan")
                    enabled: playbackEngine.bluetoothAvailable
                    onClicked: {
                        if (playbackEngine.bluetoothScanning)
                            playbackEngine.refreshBluetoothDevices()
                        else
                            playbackEngine.startBluetoothDiscovery()
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 12
                color: "#071019"
                border.width: 1
                border.color: "#1E3141"

                ListView {
                    id: bluetoothDeviceList
                    anchors.fill: parent
                    anchors.margins: 8
                    clip: true
                    spacing: 6
                    model: playbackEngine.bluetoothDevices

                    delegate: ItemDelegate {
                        id: deviceDelegate

                        width: bluetoothDeviceList.width
                        height: 62
                        leftPadding: 14
                        rightPadding: 14
                        topPadding: 8
                        bottomPadding: 8

                        property var deviceInfo: modelData

                        enabled: playbackEngine.bluetoothAvailable
                        hoverEnabled: true
                        onClicked: {
                            playbackEngine.connectBluetoothDevice(index)
                        }

                        background: Rectangle {
                            radius: 10
                            color: deviceDelegate.down
                                   ? "#173145"
                                   : (deviceDelegate.hovered
                                      ? "#102536"
                                      : "#0B1A27")
                            border.width: 1
                            border.color: deviceDelegate.deviceInfo.connected
                                          ? "#3CCFA2"
                                          : "#20384A"

                            Behavior on color {
                                ColorAnimation { duration: 120 }
                            }
                        }

                        contentItem: RowLayout {
                            spacing: 12

                            Image {
                                Layout.preferredWidth: 24
                                Layout.preferredHeight: 24
                                source: "qrc:/assets/icons/bluetooth.svg"
                                fillMode: Image.PreserveAspectFit
                            }

                            Text {
                                Layout.fillWidth: true
                                text: root.bluetoothDisplayName(deviceInfo)
                                color: "#F4F8FB"
                                font.pixelSize: 15
                                font.weight: Font.DemiBold
                                elide: Text.ElideRight
                            }

                            Text {
                                text: deviceInfo.connected
                                      ? qsTr("CONNECTED")
                                      : (deviceInfo.paired
                                         ? qsTr("PAIRED")
                                         : qsTr("CONNECT"))
                                color: deviceInfo.connected ? "#54E7B0" : root.gold
                                font.pixelSize: 10
                                font.weight: Font.DemiBold
                            }
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        visible: bluetoothDeviceList.count === 0
                        text: playbackEngine.bluetoothScanning
                              ? qsTr("Searching…")
                              : qsTr("No Bluetooth devices found")
                        color: root.secondaryText
                        font.pixelSize: 13
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                visible: playbackEngine.bluetoothConnected

                Text {
                    Layout.fillWidth: true
                    text: qsTr("Connected: ")
                          + root.bluetoothDisplayName({
                              "name": playbackEngine.bluetoothDeviceName
                          })
                    color: "#54E7B0"
                    font.pixelSize: 12
                    elide: Text.ElideRight
                }

                Button {
                    text: qsTr("Disconnect")
                    onClicked: playbackEngine.disconnectBluetoothDevice()
                }
            }
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
                               : ((root.sourceId === "usb"
                                   && !playbackEngine.usbConnected)
                                  || (root.sourceId === "bluetooth"
                                      && !playbackEngine.bluetoothConnected)
                                  ? root.gold
                                  : "#54E7B0")
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

                    // One smooth, shared visualizer for Local, Radio, USB, and
                    // Bluetooth. Bluetooth follows AVRCP playback because its
                    // output volume belongs to the Linux A2DP session.
                    readonly property bool active:
                        root.playing
                        && (root.sourceId === "bluetooth"
                            || (!root.muted && root.volumeLevel > 0.001))
                    property real phase: 0
                    property real energy: active ? 1.0 : 0.0
                    readonly property int barCount: 40
                    readonly property int cycleDuration: 2400

                    Behavior on energy {
                        NumberAnimation {
                            duration: waveform.active ? 240 : 360
                            easing.type: waveform.active
                                         ? Easing.OutCubic
                                         : Easing.InOutCubic
                        }
                    }

                    function structureAt(barIndex) {
                        var x = barIndex / Math.max(1, barCount - 1)
                        var centerEnvelope = Math.pow(
                                    Math.max(0, Math.sin(Math.PI * x)), 0.78)
                        var fineShape = 0.94
                                        + 0.06 * Math.sin(barIndex * 2.13)
                        return 0.16 + 0.76 * centerEnvelope * fineShape
                    }

                    function animatedAmplitude(barIndex) {
                        var x = barIndex / Math.max(1, barCount - 1)
                        var envelope = structureAt(barIndex)
                        var forwardWave = 0.5 + 0.5 * Math.sin(
                                    phase * 2.0 - x * Math.PI * 5.0)
                        var returnWave = 0.5 + 0.5 * Math.sin(
                                    phase * 1.35 + x * Math.PI * 8.0 + 0.8)
                        var detailPulse = 0.5 + 0.5 * Math.sin(
                                    phase * 3.1 + barIndex * 0.37)
                        var signal = 0.25
                                     + 0.46 * forwardWave
                                     + 0.19 * returnWave
                                     + 0.10 * detailPulse
                        var activeLevel = Math.min(0.96,
                                                   0.07 + envelope * signal)
                        var idleLevel = 0.065
                        return idleLevel
                               + energy * (activeLevel - idleLevel)
                    }

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.topMargin: 10
                    Layout.minimumHeight: 68

                    NumberAnimation on phase {
                        from: 0
                        to: Math.PI * 2
                        duration: waveform.cycleDuration
                        loops: Animation.Infinite
                        running: waveform.active
                        easing.type: Easing.Linear
                    }

                    Rectangle {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter

                        height: 1
                        color: "#173249"
                        opacity: waveform.active ? 0.42 : 0.72

                        Behavior on opacity {
                            NumberAnimation { duration: 240 }
                        }
                    }

                    Row {
                        id: waveRow

                        anchors.fill: parent
                        spacing: 3

                        Repeater {
                            model: waveform.barCount

                            Rectangle {
                                required property int index

                                readonly property real level:
                                    waveform.animatedAmplitude(index)

                                width: Math.max(
                                           3,
                                           (waveRow.width
                                            - (waveform.barCount - 1)
                                            * waveRow.spacing)
                                           / waveform.barCount
                                       )

                                height: Math.max(
                                            6,
                                            waveRow.height * level
                                        )

                                y: (waveRow.height - height) / 2

                                radius: width / 2
                                opacity: 0.28
                                         + waveform.energy
                                           * (0.55 + level * 0.17)

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
                      : playbackEngine.formatTime(root.elapsedMs)

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
                         && root.sourceId !== "bluetooth"
                         && !root.mediaInfo.live
                         && playbackEngine.duration > 0

                onMoved: {
                    playbackEngine.position = Math.round(
                        value * playbackEngine.duration
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
                      : playbackEngine.formatTime(
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

                iconSource: root.sourceId === "bluetooth"
                            ? "qrc:/assets/icons/bluetooth.svg"
                            : "qrc:/assets/icons/folder.svg"
                label: root.sourceId === "usb"
                       ? qsTr("Choose USB media")
                       : (root.sourceId === "bluetooth"
                          ? qsTr("Bluetooth devices")
                          : qsTr("Open library"))

                selected: root.sourceId === "usb"
                          ? usbFolderDialog.visible
                          : (root.sourceId === "bluetooth"
                             ? bluetoothDeviceDialog.visible
                             : audioFolderDialog.visible)
                highlightColor: root.cyan

                enabled: root.sourceId === "local"
                         || root.sourceId === "usb"
                         || root.sourceId === "bluetooth"
                opacity: enabled ? 1.0 : 0.35

                onClicked: {
                    if (root.sourceId === "usb")
                        usbFolderDialog.open()
                    else if (root.sourceId === "bluetooth")
                        bluetoothDeviceDialog.open()
                    else
                        audioFolderDialog.open()
                }
            }

            IconButton {
                buttonSize: 66
                iconSize: 27

                iconSource: "qrc:/assets/icons/previous.svg"
                label: qsTr("Previous")

                enabled: root.playbackAvailable
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.previous()
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

                enabled: root.playbackAvailable
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.playPause()
            }

            IconButton {
                buttonSize: 66
                iconSize: 27

                iconSource: "qrc:/assets/icons/next.svg"
                label: qsTr("Next")

                enabled: root.playbackAvailable
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.next()
            }

            IconButton {
                buttonSize: 50
                iconSize: 19

                iconSource: "qrc:/assets/icons/stop.svg"
                label: qsTr("Stop")

                enabled: root.playbackAvailable
                opacity: enabled ? 1.0 : 0.35

                onClicked: playbackEngine.stop()
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
                         && root.sourceId !== "bluetooth"
                opacity: enabled ? 1.0 : 0.35

                onClicked: {
                    playbackEngine.muted =
                        !playbackEngine.muted
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
                         && root.sourceId !== "bluetooth"
                opacity: enabled ? 1.0 : 0.35

                onMoved: {
                    playbackEngine.volume = value
                    playbackEngine.muted = false
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

        visible: playbackEngine.errorString.length > 0

        Text {
            id: playbackErrorText

            anchors.centerIn: parent

            width: parent.width - 24

            text: playbackEngine.errorString
            color: "#FFE6DF"

            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
        }
    }
}
