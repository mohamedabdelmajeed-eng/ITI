import QtQuick

Item {
    id: root

    property color primaryColor: "#47DAFF"
    property color secondaryColor: "#7C5CFF"
    property bool animated: false

    width: 112
    height: 112

    Rectangle {
        id: outerRing

        anchors.fill: parent
        radius: width / 2
        color: "transparent"
        border.width: 2
        border.color: Qt.rgba(root.primaryColor.r,
                              root.primaryColor.g,
                              root.primaryColor.b, 0.30)

        Rectangle {
            width: 8
            height: 8
            radius: 4
            color: root.primaryColor
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: -3
        }


        RotationAnimator on rotation {
            running: root.animated
            from: 0
            to: 360
            duration: 7500
            loops: Animation.Infinite
        }
    }

    Rectangle {
        anchors.centerIn: parent
        width: parent.width * 0.76
        height: width
        radius: width / 2
        color: "#101B2A"
        border.width: 1
        border.color: Qt.rgba(root.secondaryColor.r,
                              root.secondaryColor.g,
                              root.secondaryColor.b, 0.55)

        Rectangle {
            anchors.centerIn: parent
            width: parent.width * 0.68
            height: width
            radius: 18
            rotation: 45

            gradient: Gradient {
                GradientStop { position: 0.0; color: root.primaryColor }
                GradientStop { position: 1.0; color: root.secondaryColor }
            }
        }

        Row {
            anchors.centerIn: parent
            spacing: 5
            rotation: 0

            Repeater {
                model: [18, 32, 46, 32, 18]

                Rectangle {
                    // req for prop must resieve value
                    required property int modelData

                    width: 5
                    height: modelData
                    radius: 3
                    color: "#F5FBFF"
                }
            }
        }
    }
}
