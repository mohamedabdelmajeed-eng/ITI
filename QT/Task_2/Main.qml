import QtQuick
import QtQuick.Window

Window {
    id: root

    width: 1000
    height: 650
    visible: true
    title: "Auto Car"

    property bool showSplash: true

    Timer {
        interval: 3000
        running: true
        repeat: false

        onTriggered: {
            root.showSplash = false
        }
    }

    // =========================
    // Home Screen
    // =========================

    Rectangle {
        id: homeScreen

        anchors.fill: parent
        color: "#f2f2f2"

        visible: !root.showSplash

        Column {
            anchors.fill: parent
            spacing: 20

            Rectangle {
                width: parent.width
                height: 80
                color: "#202020"

                Text {
                    anchors.centerIn: parent

                    text: "Car Products"
                    color: "white"

                    font.pixelSize: 30
                    font.bold: true
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                CarCard {
                    carName: "BMW M4"
                    carImage: "qrc:/qt/qml/Task_2/images/car1.jpg"
                    carColor: "Black"
                    carType: "Sports Coupe"
                    carModel: "2025"
                }

                CarCard {
                    carName: "Black Supercar"
                    carImage: "qrc:/qt/qml/Task_2/images/car2.jpg"
                    carColor: "Black"
                    carType: "Supercar"
                    carModel: "2024"
                }

                CarCard {
                    carName: "Mercedes AMG GT"
                    carImage: "qrc:/qt/qml/Task_2/images/car3.jpg"
                    carColor: "Yellow"
                    carType: "Sports Car"
                    carModel: "2025"
                }
            }
        }
    }

    // =========================
    // Splash Screen
    // =========================

    Rectangle {
        id: splashScreen

        anchors.fill: parent
        color: "white"

        visible: root.showSplash
        z: 10

        Column {
            anchors.centerIn: parent
            spacing: 20

            Image {
                width: 260
                height: 220

                anchors.horizontalCenter: parent.horizontalCenter

                source: "qrc:/qt/qml/Task_2/images/logo.png"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Welcome to Auto Car"
                color: "#202020"

                font.pixelSize: 30
                font.bold: true
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Loading..."
                color: "gray"
                font.pixelSize: 18
            }
        }
    }
}