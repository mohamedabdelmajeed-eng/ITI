import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    required property var appWindow
    required property var navigationStack

    property string backgroundImage: "qrc:/Images/dashboard.png"

    implicitHeight: 280

    radius: 28
    clip: true

    color: "#101012"

    border.color: "#4C3B20"
    border.width: 1

    // =========================================================
    // Dashboard background image
    // =========================================================

    Image {
        anchors.fill: parent

        source: root.backgroundImage

        fillMode: Image.PreserveAspectCrop

        smooth: true
        asynchronous: true
    }

    // =========================================================
    // Dark overlay
    // =========================================================

    Rectangle {
        anchors.fill: parent

        color: "#08090B"
        opacity: 0.55
    }

    // =========================================================
    // Welcome content
    // =========================================================

    Column {
        anchors.left: parent.left
        anchors.leftMargin: 45

        anchors.verticalCenter: parent.verticalCenter

        spacing: 10

        Label {
            text: qsTr("Welcome Home")

            color: appWindow.mainTextColor

            font.pixelSize: 36
            font.bold: true
        }

        Label {
            text: qsTr("Everything is ready for your comfort")

            color: appWindow.secondaryTextColor

            font.pixelSize: 16
        }

        Item {
            width: 1
            height: 8
        }

        Rectangle {
            width: 190
            height: 74

            radius: 18

            color: "#B0151517"

            border.color: "#6A522B"
            border.width: 1

            Row {
                anchors.centerIn: parent

                spacing: 15

                Label {
                    text: "24°C"

                    color: appWindow.brightGoldColor

                    font.pixelSize: 25
                    font.bold: true
                }

                Label {
                    text: qsTr("Comfort Mode")

                    color: appWindow.secondaryTextColor

                    font.pixelSize: 13

                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    // =========================================================
    // Settings button
    // =========================================================

    Button {
        id: settingsButton

        width: 130
        height: 50

        anchors.top: parent.top
        anchors.topMargin: 28

        anchors.right: parent.right
        anchors.rightMargin: 30

        text: qsTr("Settings")

        onClicked: {
            navigationStack.push(
                Qt.resolvedUrl("SettingsPage.qml"),
                {
                    "appWindow": appWindow,
                    "navigationStack": navigationStack
                }
            )
        }

        background: Rectangle {
            radius: 14

            color: settingsButton.down
                   ? "#262629"
                   : "#171719"

            border.color: appWindow.goldColor
            border.width: 1
        }

        contentItem: Text {
            text: settingsButton.text

            color: appWindow.mainTextColor

            font.pixelSize: 14
            font.bold: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}