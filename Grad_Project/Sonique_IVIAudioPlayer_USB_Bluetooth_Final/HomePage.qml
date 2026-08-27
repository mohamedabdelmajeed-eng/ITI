import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    //communicate wth main QML
    signal sourceRequested(string sourceId,
                           string sourceTitle,
                           color accentColor,
                           string iconText)

    property string selectedTitle: qsTr("No source selected")
    property color selectedAccent: "#47DAFF"
    //Background
    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#070B12" }
            GradientStop { position: 0.6; color: "#09121B" }
            GradientStop { position: 1.0; color: "#080D15" }
        }
    }
    //top right decoative cir
    Rectangle {
        width: 520
        height: 520
        radius: width / 2
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: -230
        anchors.topMargin: -290
        color: "#183A52"
        opacity: 0.13
    }
    // complete home page content vertically
    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: Math.max(34, root.width * 0.048)
        anchors.rightMargin: Math.max(34, root.width * 0.048)
        anchors.topMargin: 25
        anchors.bottomMargin: 24
        spacing: 0
    // the header
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 62

            Row {
                Layout.alignment: Qt.AlignVCenter
                spacing: 13

                IVILogo {
                    width: 48
                    height: 48
                    primaryColor: "#47DAFF"
                    secondaryColor: "#7C5CFF"
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 2

                    Text {
                        text: qsTr("SONIQUE")
                        color: "#F3F8FC"
                        font.pixelSize: 16
                        font.weight: Font.DemiBold
                        font.letterSpacing: 2.5
                    }

                    Text {
                        text: qsTr("IVI AUDIO")
                        color: "#587286"
                        font.pixelSize: 9
                        font.weight: Font.Medium
                        font.letterSpacing: 2
                    }
                }
            }

            Item { Layout.fillWidth: true }// spacer bet logo and timer

            Rectangle {
                Layout.preferredWidth: readyRow.implicitWidth + 28
                Layout.preferredHeight: 34
                Layout.alignment: Qt.AlignVCenter
                radius: 17
                color: "#0D1B24"
                border.width: 1
                border.color: "#183444"

                Row {
                    id: readyRow
                    anchors.centerIn: parent
                    spacing: 8

                    Rectangle {
                        width: 7
                        height: 7
                        radius: 4
                        color: "#4BE3A6"
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        text: qsTr("SYSTEM READY")
                        color: "#82A0B2"
                        font.pixelSize: 9
                        font.weight: Font.DemiBold
                        font.letterSpacing: 1.1
                    }
                }
            }

            Column {
                id: clock

                property date now: new Date() // right is java script new date and time object

                Layout.leftMargin: 18
                Layout.alignment: Qt.AlignVCenter
                spacing: 1

                Text {
                    anchors.right: parent.right
                    text: Qt.formatTime(clock.now, "hh:mm")//converts a time into formatted text.
                    color: "#EEF5F9"
                    font.pixelSize: 23
                    font.weight: Font.DemiBold
                }

                Text {
                    anchors.right: parent.right
                    text: Qt.formatDate(clock.now, "ddd, MMM d").toUpperCase()
                    color: "#587286"
                    font.pixelSize: 9
                    font.weight: Font.Medium
                    font.letterSpacing: 1
                }

                Timer {
                    interval: 1000
                    running: true
                    repeat: true
                    onTriggered: clock.now = new Date()
                }
            }
        }

        Item { Layout.preferredHeight: Math.max(24, root.height * 0.045) } //spacer between logo and heade

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 7

            Text {
                text: qsTr("Choose your audio source")
                color: "#F2F7FA"
                font.pixelSize: root.width < 1000 ? 29 : 36
                font.weight: Font.DemiBold
            }

            Text {
                text: qsTr("Your music, stations and connected devices — all in one place.")
                color: "#647E91"
                font.pixelSize: 13
            }
        }

        Item { Layout.preferredHeight: 23 }

        GridLayout {
            id: sourceGrid

            Layout.fillWidth: true
            Layout.preferredHeight: Math.min(300, Math.max(236, root.height * 0.38))
            columns: root.width >= 900 ? 4 : 2//if HomePage were reused inside a smaller container.
            columnSpacing: 16
            rowSpacing: 16

            Repeater {
                model: [
                    {
                        "sourceId": "local",
                        "title": qsTr("Local Media"),
                        "description": qsTr("Music stored inside your IVI system."),
                        "status": qsTr("ON DEVICE"),
                        "icon": "♪",
                        "accent": "#47DAFF"
                    },
                    {
                        "sourceId": "radio",
                        "title": qsTr("Radio"),
                        "description": qsTr("Browse live stations and saved presets."),
                        "status": qsTr("LIVE"),
                        "icon": "FM",
                        "accent": "#FFB85C"
                    },
                    {
                        "sourceId": "usb",
                        "title": qsTr("USB Media"),
                        "description": qsTr("Connect a drive and explore its library."),
                        "status": qsTr("PLUG IN"),
                        "icon": "USB",
                        "accent": "#9D7BFF"
                    },
                    {
                        "sourceId": "bluetooth",
                        "title": qsTr("Bluetooth"),
                        "description": qsTr("Pair a phone and stream audio wirelessly."),
                        "status": qsTr("PAIR"),
                        "icon": "BT",
                        "accent": "#4BE3A6"
                    }
                ]

                SourceCard {
                    required property var modelData

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumHeight: 228
                    sourceId: modelData.sourceId
                    title: modelData.title
                    description: modelData.description
                    statusText: modelData.status
                    iconText: modelData.icon
                    accentColor: modelData.accent

                    onClicked: {
                        root.selectedTitle = title
                        root.selectedAccent = accentColor
                        root.sourceRequested(sourceId, title, accentColor, iconText)
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.minimumHeight: 18
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 72
            radius: 20
            color: "#0C151F"
            border.width: 1
            border.color: "#172735"

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 18
                spacing: 14

                Rectangle {
                    Layout.preferredWidth: 43
                    Layout.preferredHeight: 43
                    radius: 13
                    color: Qt.rgba(root.selectedAccent.r,
                                   root.selectedAccent.g,
                                   root.selectedAccent.b, 0.12)

                    Text {
                        anchors.centerIn: parent
                        text: "♪"
                        color: root.selectedAccent
                        font.pixelSize: 23
                    }
                }

                Column {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    spacing: 3

                    Text {
                        text: root.selectedTitle
                        color: "#DBE7ED"
                        font.pixelSize: 13
                        font.weight: Font.DemiBold
                    }

                    Text {
                        text: qsTr("Select a source to start listening")
                        color: "#526D80"
                        font.pixelSize: 10
                    }
                }

                Text {
                    text: qsTr("FRONTEND 01")
                    color: "#405969"
                    font.pixelSize: 9
                    font.weight: Font.Medium
                    font.letterSpacing: 1.3
                }
            }
        }
    }
}
