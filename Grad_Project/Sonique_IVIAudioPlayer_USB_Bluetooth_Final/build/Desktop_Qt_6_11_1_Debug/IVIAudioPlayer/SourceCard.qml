import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    property string sourceId: ""
    property string title: ""
    property string description: ""
    property string statusText: "READY"
    property string iconText: "♪"
    property color accentColor: "#47DAFF"

    signal clicked()

    implicitWidth: 260
    implicitHeight: 230
    radius: 24
    color: mouseArea.pressed ? "#152131" : (mouseArea.containsMouse ? "#121D2A" : "#0E1722")
    border.width: 1
    border.color: mouseArea.containsMouse
                  ? Qt.rgba(accentColor.r, accentColor.g, accentColor.b, 0.72)
                  : "#1A2A38"
    scale: mouseArea.pressed ? 0.975 : 1.0
    clip: true
    //Automatically animates changes to a property.
    Behavior on color { ColorAnimation { duration: 160 } }
    Behavior on border.color { ColorAnimation { duration: 160 } }
    Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutCubic } }
    //left strip
    Rectangle {
        width: 5
        height: parent.height * 0.44
        radius: 3
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: root.accentColor
    }
    // top rigt decorative cir
    Rectangle {
        width: 170
        height: 170
        radius: width / 2
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: -75
        anchors.topMargin: -82
        color: root.accentColor
        opacity: mouseArea.containsMouse ? 0.1 : 0.055

        Behavior on opacity { NumberAnimation { duration: 180 } }
    }
    //main content
    Column {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 0

        Item {
            width: parent.width
            height: 78
            //icon rect
            Rectangle {
                width: 62
                height: 62
                radius: 18
                color: Qt.rgba(root.accentColor.r,
                               root.accentColor.g,
                               root.accentColor.b, 0.13)
                border.width: 1
                border.color: Qt.rgba(root.accentColor.r,
                                      root.accentColor.g,
                                      root.accentColor.b, 0.34)

                Text {
                    anchors.centerIn: parent
                    text: root.iconText
                    color: root.accentColor
                    font.pixelSize: root.iconText.length > 1 ? 18 : 32
                    font.weight: Font.DemiBold
                    font.letterSpacing: root.iconText.length > 1 ? 1 : 0
                }
            }
            //status badge
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                width: statusLabel.implicitWidth + 20
                height: 28
                radius: 14
                color: Qt.rgba(root.accentColor.r,
                               root.accentColor.g,
                               root.accentColor.b, 0.10)

                Text {
                    id: statusLabel
                    anchors.centerIn: parent
                    text: root.statusText
                    color: root.accentColor
                    font.pixelSize: 9
                    font.weight: Font.DemiBold
                    font.letterSpacing: 1
                }
            }
        }
        //source title
        Text {
            width: parent.width
            text: root.title
            color: "#F1F6FA"
            font.pixelSize: 21
            font.weight: Font.DemiBold
            elide: Text.ElideRight//If the title is too long, remove characters from the right and show an ellipsis.
        }
        //description
        Text {
            width: parent.width
            topPadding: 8// spacer
            text: root.description
            color: "#71889A"
            font.pixelSize: 12
            lineHeight: 1.25
            wrapMode: Text.WordWrap //moves complete words to the next line.
            maximumLineCount: 2
            elide: Text.ElideRight
        }

        Item { width: 1; height: 17 }

        Row {
            spacing: 8

            Text {
                text: qsTr("OPEN SOURCE")
                color: root.accentColor
                font.pixelSize: 10
                font.weight: Font.DemiBold
                font.letterSpacing: 1.1
            }

            Text {
                text: "›"
                color: root.accentColor
                font.pixelSize: 17
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -1
            }
        }
    }
    //makes the card interactive.
    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}
