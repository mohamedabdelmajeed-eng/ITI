import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {
    id: root

    // =========================================================
    // Properties
    // =========================================================

    required property var appWindow

    property string deviceName: ""
    property string deviceImage: ""

    property bool deviceOn: false
    property real energyValue: 0.50


    // =========================================================
    // Custom signal
    // =========================================================

    signal deviceStateChanged(bool newState)


    // =========================================================
    // Card size / appearance
    // =========================================================

    implicitWidth: 245
    implicitHeight: 355

    radius: 22

    color: "#131416"

    border.color:
        root.deviceOn
        ? appWindow.goldColor
        : "#3E3E41"

    border.width: 1


    // =========================================================
    // Main content
    // =========================================================

    ColumnLayout {
        anchors.fill: parent

        anchors.leftMargin: 14
        anchors.rightMargin: 14
        anchors.topMargin: 14
        anchors.bottomMargin: 14

        spacing: 9


        // =====================================================
        // Device image container
        // =====================================================

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 165

            radius: 18

            color: "#0B0C0E"

            border.color:
                root.deviceOn
                ? "#755821"
                : "#363638"

            border.width: 1

            clip: true


            Image {
                anchors.fill: parent
                anchors.margins: 10

                source: root.deviceImage

                fillMode: Image.PreserveAspectFit

                smooth: true
                asynchronous: true
            }
        }


        // =====================================================
        // Device name
        // =====================================================

        Label {
            Layout.fillWidth: true
            Layout.preferredHeight: 28

            text: root.deviceName

            color: appWindow.mainTextColor

            font.pixelSize: 16
            font.bold: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight
        }


        // =====================================================
        // State + Switch
        // =====================================================

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 42

            spacing: 8


            // -------------------------------------------------
            // ON / OFF text
            // -------------------------------------------------

            Label {
                Layout.fillWidth: true

                text:
                    root.deviceOn
                    ? qsTr("On")
                    : qsTr("Off")

                color:
                    root.deviceOn
                    ? appWindow.brightGoldColor
                    : appWindow.secondaryTextColor

                font.pixelSize: 13
                font.bold: true

                verticalAlignment: Text.AlignVCenter
            }


            // -------------------------------------------------
            // Premium Switch
            // -------------------------------------------------

            Switch {
                id: deviceSwitch

                // CRITICAL FIX:
                // Explicit size prevents Qt's default
                // Switch implicit size from overflowing.
                Layout.preferredWidth: 60
                Layout.minimumWidth: 60
                Layout.maximumWidth: 60

                Layout.preferredHeight: 32
                Layout.minimumHeight: 32
                Layout.maximumHeight: 32

                Layout.alignment: Qt.AlignVCenter

                checked: root.deviceOn

                hoverEnabled: true


                // =============================================
                // Remove default text/content area
                // =============================================

                contentItem: Item {
                    implicitWidth: 0
                    implicitHeight: 0
                }


                // =============================================
                // Custom switch track
                // =============================================

                indicator: Rectangle {
                    width: 56
                    height: 28

                    x: 2
                    y: 2

                    radius: 14

                    color:
                        deviceSwitch.checked
                        ? "#C99730"
                        : "#34363A"

                    border.color:
                        deviceSwitch.checked
                        ? appWindow.brightGoldColor
                        : "#53555A"

                    border.width: 1


                    // =========================================
                    // Switch handle
                    // =========================================

                    Rectangle {
                        width: 22
                        height: 22

                        radius: 11

                        anchors.verticalCenter:
                            parent.verticalCenter

                        x:
                            deviceSwitch.checked
                            ? parent.width - width - 3
                            : 3

                        color: "#F6F3ED"

                        border.color:
                            deviceSwitch.checked
                            ? "#F4D174"
                            : "#CBCBCB"

                        border.width: 1


                        Behavior on x {
                            NumberAnimation {
                                duration: 170
                                easing.type: Easing.OutCubic
                            }
                        }
                    }


                    Behavior on color {
                        ColorAnimation {
                            duration: 150
                        }
                    }
                }


                // =============================================
                // Switch logic
                // =============================================

                onToggled: {

                    root.deviceOn = checked

                    console.log(
                        root.deviceName,
                        checked ? "ON" : "OFF"
                    )

                    root.deviceStateChanged(
                        checked
                    )
                }
            }
        }


        // =====================================================
        // Separator
        // =====================================================

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 1

            color: "#333438"
        }


        // =====================================================
        // Energy information
        // =====================================================

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 22


            Label {
                Layout.fillWidth: true

                text: qsTr("Energy Usage")

                color: appWindow.secondaryTextColor

                font.pixelSize: 10
            }


            Label {
                text:
                    Math.round(
                        root.energyValue * 100
                    ) + "%"

                color: appWindow.brightGoldColor

                font.pixelSize: 11
                font.bold: true

                horizontalAlignment: Text.AlignRight
            }
        }


        // =====================================================
        // Progress Bar
        // =====================================================

        ProgressBar {
            id: energyBar

            Layout.fillWidth: true
            Layout.preferredHeight: 8

            from: 0
            to: 1

            value: root.energyValue


            background: Rectangle {
                radius: 4

                color: "#34363A"
            }


            contentItem: Item {

                Rectangle {
                    width:
                        energyBar.visualPosition
                        * parent.width

                    height: parent.height

                    radius: 4

                    color:
                        appWindow.goldColor
                }
            }
        }
    }
}