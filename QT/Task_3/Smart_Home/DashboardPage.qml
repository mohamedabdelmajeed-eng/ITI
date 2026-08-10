import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Page {
    id: root

    required property var appWindow
    required property var navigationStack


    // =========================================================
    // Page background
    // =========================================================

    background: Rectangle {
        color: appWindow.backgroundColor
    }


    // =========================================================
    // Scrollable Dashboard
    // =========================================================

    ScrollView {
        id: scrollView

        anchors.fill: parent

        clip: true

        ScrollBar.horizontal.policy:
            ScrollBar.AlwaysOff


        Column {
            id: dashboardContent

            width: scrollView.availableWidth

            spacing: 22


            // =================================================
            // Hero
            // =================================================

            HeroSection {
                width: parent.width - 36

                anchors.horizontalCenter:
                    parent.horizontalCenter

                appWindow:
                    root.appWindow

                navigationStack:
                    root.navigationStack

                backgroundImage:
                    "qrc:/Images/dashboard.png"
            }


            // =================================================
            // MY DEVICES
            // =================================================

            Column {
                width: parent.width - 36

                anchors.horizontalCenter:
                    parent.horizontalCenter

                spacing: 15


                // =============================================
                // Section title
                // =============================================

                Row {
                    spacing: 10


                    Label {
                        text: "▦"

                        color:
                            appWindow.goldColor

                        font.pixelSize: 22
                    }


                    Label {
                        text:
                            qsTr("My Devices")

                        color:
                            appWindow.brightGoldColor

                        font.pixelSize: 24
                        font.bold: true
                    }


                    Label {
                        text: "✦"

                        color:
                            appWindow.goldColor

                        font.pixelSize: 16

                        anchors.verticalCenter:
                            parent.verticalCenter
                    }
                }


                // =============================================
                // Device Grid
                // =============================================

                GridLayout {
                    id: devicesGrid

                    width: parent.width

                    columns: 5

                    columnSpacing: 14
                    rowSpacing: 14


                    // =========================================
                    // Living Room Light
                    // =========================================

                    DeviceCard {
                        id: livingRoomLight

                        Layout.fillWidth: true

                        Layout.minimumWidth: 0
                        Layout.preferredWidth: 1

                        appWindow:
                            root.appWindow

                        deviceName:
                            qsTr(
                                "Living Room Light"
                            )

                        deviceImage:
                            "qrc:/Images/light.png"

                        deviceOn: true

                        energyValue: 0.72
                    }


                    // =========================================
                    // Bedroom Light
                    // =========================================

                    DeviceCard {
                        id: bedroomLight

                        Layout.fillWidth: true

                        Layout.minimumWidth: 0
                        Layout.preferredWidth: 1

                        appWindow:
                            root.appWindow

                        deviceName:
                            qsTr(
                                "Bedroom Light"
                            )

                        deviceImage:
                            "qrc:/Images/light.png"

                        deviceOn: true

                        energyValue: 0.48
                    }


                    // =========================================
                    // Air Conditioner
                    // =========================================

                    DeviceCard {
                        id: airConditioner

                        Layout.fillWidth: true

                        Layout.minimumWidth: 0
                        Layout.preferredWidth: 1

                        appWindow:
                            root.appWindow

                        deviceName:
                            qsTr(
                                "Air Conditioner"
                            )

                        deviceImage:
                            "qrc:/Images/air.png"

                        deviceOn: true

                        energyValue: 0.83
                    }


                    // =========================================
                    // Fan
                    // =========================================

                    DeviceCard {
                        id: fan

                        Layout.fillWidth: true

                        Layout.minimumWidth: 0
                        Layout.preferredWidth: 1

                        appWindow:
                            root.appWindow

                        deviceName:
                            qsTr("Fan")

                        deviceImage:
                            "qrc:/Images/fan.png"

                        deviceOn: false

                        energyValue: 0.35
                    }


                    // =========================================
                    // Garage Door
                    // =========================================

                    DeviceCard {
                        id: garage

                        Layout.fillWidth: true

                        Layout.minimumWidth: 0
                        Layout.preferredWidth: 1

                        appWindow:
                            root.appWindow

                        deviceName:
                            qsTr(
                                "Garage Door"
                            )

                        deviceImage:
                            "qrc:/Images/garage.png"

                        deviceOn: false

                        energyValue: 0.60
                    }
                }
            }


            // =================================================
            // Quick Actions
            // =================================================

            QuickActions {
                width: parent.width - 36

                anchors.horizontalCenter:
                    parent.horizontalCenter

                appWindow:
                    root.appWindow

                livingRoomLight:
                    livingRoomLight

                bedroomLight:
                    bedroomLight

                airConditioner:
                    airConditioner

                fan:
                    fan

                garage:
                    garage
            }


            // =================================================
            // Bottom spacing
            // =================================================

            Item {
                width: 1
                height: 28
            }
        }
    }
}