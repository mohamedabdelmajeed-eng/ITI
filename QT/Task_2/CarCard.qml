import QtQuick

Rectangle {
    id: card

    width: 280
    height: 390

    color: "white"
    radius: 15

    border.color: "#999999"
    border.width: 2

    clip: true

    property string carName: ""
    property url carImage: ""
    property string carColor: ""
    property string carType: ""
    property string carModel: ""

    property bool showDetails: false

    // =========================
    // Normal Card
    // =========================

    Column {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 12

        visible: !card.showDetails

        Image {
            id: productImage

            width: parent.width
            height: 230

            source: card.carImage
            fillMode: Image.PreserveAspectCrop

            clip: true

            MouseArea {
                anchors.fill: parent

                cursorShape: Qt.PointingHandCursor

                onClicked: {
                    card.showDetails = true
                }
            }
        }

        Text {
            width: parent.width

            text: card.carName

            font.pixelSize: 22
            font.bold: true

            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            width: parent.width

            text: "Click image for details"
            color: "gray"
            font.pixelSize: 14

            horizontalAlignment: Text.AlignHCenter
        }
    }

    // =========================
    // Details
    // =========================

    Rectangle {
        anchors.fill: parent

        visible: card.showDetails
        color: "#eeeeee"

        Column {
            anchors.centerIn: parent
            spacing: 18

            Text {
                anchors.horizontalCenter: parent.horizontalCenter

                text: card.carName

                font.pixelSize: 24
                font.bold: true
            }

            Text {
                text: "Color: " + card.carColor
                font.pixelSize: 18
            }

            Text {
                text: "Type: " + card.carType
                font.pixelSize: 18
            }

            Text {
                text: "Model: " + card.carModel
                font.pixelSize: 18
            }

            Rectangle {
                width: 160
                height: 48

                anchors.horizontalCenter: parent.horizontalCenter

                radius: 10
                color: "#c62828"

                Text {
                    anchors.centerIn: parent

                    text: "Hide Details"
                    color: "white"

                    font.pixelSize: 16
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent

                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        card.showDetails = false
                    }
                }
            }
        }
    }
}