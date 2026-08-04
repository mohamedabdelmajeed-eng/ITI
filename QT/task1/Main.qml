import QtQuick
import QtQuick.Window

Window {
    width: 600
    height: 400
    visible: true
    title: qsTr("My Information")

    Rectangle {
        width: 400
        height: 250
        color: "lightblue"
        radius: 15

        anchors.centerIn: parent

        Column {
            anchors.centerIn: parent
            spacing: 15

            Text {
                text: "Hello World!"
                font.pixelSize: 28
                font.bold: true
            }

            Text {
                text: "I am: Mohamed Abdelmajeed"
                font.pixelSize: 20
            }

            Text {
                text: "ID: 248339"
                font.pixelSize: 20
            }

            Text {
                text: "Worked At: A Company"
                font.pixelSize: 20
            }

            Text {
                text: "City: 6th October"
                font.pixelSize: 20
            }
        }
    }
}
