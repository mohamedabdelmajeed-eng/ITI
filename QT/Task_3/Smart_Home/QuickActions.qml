import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {
    id: root

    // =========================================================
    // References
    // =========================================================

    required property var appWindow

    required property var livingRoomLight
    required property var bedroomLight
    required property var airConditioner
    required property var fan
    required property var garage


    // =========================================================
    // Main panel
    // =========================================================

    implicitHeight: 185

    radius: 24

    color: "#131416"

    border.color: "#574526"
    border.width: 1


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 18

        spacing: 14


        // =====================================================
        // Section title
        // =====================================================

        RowLayout {
            Layout.fillWidth: true

            spacing: 10


            Label {
                text: "ϟ"

                color:
                    appWindow.goldColor

                font.pixelSize: 22
            }


            Label {
                text:
                    qsTr("Quick Actions")

                color:
                    appWindow.brightGoldColor

                font.pixelSize: 21
                font.bold: true
            }


            Label {
                text: "✦"

                color:
                    appWindow.goldColor

                font.pixelSize: 16
            }


            Item {
                Layout.fillWidth: true
            }
        }


        // =====================================================
        // Action cards
        // =====================================================

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            spacing: 14


            // =================================================
            // ALL OFF
            // =================================================

            Button {
                id: allOffButton

                Layout.fillWidth: true
                Layout.fillHeight: true

                Layout.minimumWidth: 0
                Layout.preferredWidth: 1

                hoverEnabled: true


                onClicked: {

                    livingRoomLight.deviceOn =
                            false

                    bedroomLight.deviceOn =
                            false

                    airConditioner.deviceOn =
                            false

                    fan.deviceOn =
                            false

                    garage.deviceOn =
                            false

                    console.log(
                        "All devices turned OFF"
                    )
                }


                background: Rectangle {
                    radius: 18

                    color:
                        allOffButton.down
                        ? "#4C1111"
                        : allOffButton.hovered
                          ? "#3B1010"
                          : "#291010"

                    border.color:
                        "#A92E27"

                    border.width: 1


                    Behavior on color {
                        ColorAnimation {
                            duration: 150
                        }
                    }
                }


                contentItem: RowLayout {
                    spacing: 14


                    Rectangle {
                        Layout.preferredWidth: 58
                        Layout.preferredHeight: 58

                        radius: 29

                        color: "#4E1515"

                        border.color:
                            "#E23C33"

                        border.width: 1


                        Label {
                            anchors.centerIn:
                                parent

                            text: "⏻"

                            color: "#FF5147"

                            font.pixelSize: 30
                            font.bold: true
                        }
                    }


                    ColumnLayout {
                        Layout.fillWidth: true

                        spacing: 3


                        Label {
                            text:
                                qsTr("ALL OFF")

                            color: "#FFFFFF"

                            font.pixelSize: 17
                            font.bold: true

                            font.letterSpacing: 1
                        }


                        Label {
                            text:
                                qsTr(
                                    "Turn off all devices"
                                )

                            color: "#C69D9A"

                            font.pixelSize: 12

                            elide:
                                Text.ElideRight
                        }
                    }


                    Label {
                        text: "›"

                        color: "#F14A42"

                        font.pixelSize: 31
                    }
                }
            }


            // =================================================
            // COMFORT MODE
            // =================================================

            Button {
                id: comfortButton

                Layout.fillWidth: true
                Layout.fillHeight: true

                Layout.minimumWidth: 0
                Layout.preferredWidth: 1

                hoverEnabled: true


                onClicked: {

                    livingRoomLight.deviceOn =
                            true

                    bedroomLight.deviceOn =
                            true

                    airConditioner.deviceOn =
                            true

                    fan.deviceOn =
                            false

                    garage.deviceOn =
                            false

                    console.log(
                        "Comfort Mode activated"
                    )
                }


                background: Rectangle {
                    radius: 18

                    color:
                        comfortButton.down
                        ? "#493512"
                        : comfortButton.hovered
                          ? "#3C2D11"
                          : "#2A220E"

                    border.color:
                        appWindow.goldColor

                    border.width: 1


                    Behavior on color {
                        ColorAnimation {
                            duration: 150
                        }
                    }
                }


                contentItem: RowLayout {
                    spacing: 14


                    Rectangle {
                        Layout.preferredWidth: 58
                        Layout.preferredHeight: 58

                        radius: 29

                        color: "#40300F"

                        border.color:
                            appWindow.brightGoldColor

                        border.width: 1


                        Label {
                            anchors.centerIn:
                                parent

                            text: "◇"

                            color:
                                appWindow.brightGoldColor

                            font.pixelSize: 29
                            font.bold: true
                        }
                    }


                    ColumnLayout {
                        Layout.fillWidth: true

                        spacing: 3


                        Label {
                            text:
                                qsTr(
                                    "COMFORT MODE"
                                )

                            color: "#FFFFFF"

                            font.pixelSize: 17
                            font.bold: true

                            font.letterSpacing: 1
                        }


                        Label {
                            text:
                                qsTr(
                                    "Optimize for comfort"
                                )

                            color: "#C9B99A"

                            font.pixelSize: 12

                            elide:
                                Text.ElideRight
                        }
                    }


                    Label {
                        text: "›"

                        color:
                            appWindow.brightGoldColor

                        font.pixelSize: 31
                    }
                }
            }


            // =================================================
            // GOOD NIGHT
            // =================================================

            Button {
                id: goodNightButton

                Layout.fillWidth: true
                Layout.fillHeight: true

                Layout.minimumWidth: 0
                Layout.preferredWidth: 1

                hoverEnabled: true


                onClicked: {

                    livingRoomLight.deviceOn =
                            false

                    bedroomLight.deviceOn =
                            false

                    fan.deviceOn =
                            false

                    garage.deviceOn =
                            false

                    airConditioner.deviceOn =
                            true

                    console.log(
                        "Good Night mode activated"
                    )
                }


                background: Rectangle {
                    radius: 18

                    color:
                        goodNightButton.down
                        ? "#102B44"
                        : goodNightButton.hovered
                          ? "#10253A"
                          : "#0D1A28"

                    border.color:
                        "#285A85"

                    border.width: 1


                    Behavior on color {
                        ColorAnimation {
                            duration: 150
                        }
                    }
                }


                contentItem: RowLayout {
                    spacing: 14


                    Rectangle {
                        Layout.preferredWidth: 58
                        Layout.preferredHeight: 58

                        radius: 29

                        color: "#143149"

                        border.color:
                            "#3370A3"

                        border.width: 1


                        Label {
                            anchors.centerIn:
                                parent

                            text: "☾"

                            color:
                                appWindow.brightGoldColor

                            font.pixelSize: 34
                        }
                    }


                    ColumnLayout {
                        Layout.fillWidth: true

                        spacing: 3


                        Label {
                            text:
                                qsTr(
                                    "GOOD NIGHT"
                                )

                            color: "#FFFFFF"

                            font.pixelSize: 17
                            font.bold: true

                            font.letterSpacing: 1
                        }


                        Label {
                            text:
                                qsTr(
                                    "Prepare for a good sleep"
                                )

                            color: "#AAC0D2"

                            font.pixelSize: 12

                            elide:
                                Text.ElideRight
                        }
                    }


                    Label {
                        text: "›"

                        color: "#AAC0D2"

                        font.pixelSize: 31
                    }
                }
            }
        }
    }
}