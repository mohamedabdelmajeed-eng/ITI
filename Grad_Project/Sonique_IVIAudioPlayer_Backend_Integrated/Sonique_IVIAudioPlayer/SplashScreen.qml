import QtQuick

Item {
    id: root

    signal finished()

    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#050810" }
            GradientStop { position: 0.55; color: "#09131F" }
            GradientStop { position: 1.0; color: "#080A12" }
        }
    }

    Rectangle {
        width: Math.max(root.width, root.height) * 0.78
        height: width
        radius: width / 2
        anchors.centerIn: parent
        color: "transparent"
        border.width: 1.5
        border.color: "#112B3D"
        opacity: 0.60
    }

    Rectangle {
        width: Math.max(root.width, root.height) * 0.52
        height: width
        radius: width / 2
        anchors.centerIn: parent
        color: "transparent"
        border.width: 1
        border.color: "#171D3B"
        opacity: 0.70
    }

    Item {
        id: glow

        width: 360
        height: 360
        anchors.centerIn: parent
        opacity: 0.18

        Rectangle {
            anchors.fill: parent
            radius: width / 2
            color: "#47DAFF"
            opacity: 0.1
            scale: 0.8

            SequentialAnimation on scale {
                running: true
                loops: Animation.Infinite
                NumberAnimation { to: 1.09; duration: 1400; easing.type: Easing.InOutSine }
                NumberAnimation { to: 0.9; duration: 1400; easing.type: Easing.InOutSine }
            }
        }
    }

    Column {
        id: splashContent

        anchors.centerIn: parent
        anchors.verticalCenterOffset: -8// Moves an object relative to its vertical-center anchor.


        spacing: 22
        opacity: 0
        scale: 0.84

        IVILogo {
            width: 132
            height: 132
            anchors.horizontalCenter: parent.horizontalCenter
            primaryColor: "#47DAFF"
            secondaryColor: "#7C5CFF"
            animated: true
        }

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 7

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("SONIQUE")
                color: "#F4F9FF"
                font.pixelSize: 31
                font.weight: Font.DemiBold
                font.letterSpacing: 6
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("IVI AUDIO SYSTEM")
                color: "#7690A5"
                font.pixelSize: 12
                font.weight: Font.Medium
                font.letterSpacing: 3
            }
        }

        Item {
            width: 230
            height: 20
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                width: parent.width
                height: 2
                radius: 1
                anchors.verticalCenter: parent.verticalCenter
                color: "#172431"
            }

            Rectangle {
                id: progressLine

                width: 0
                height: 2
                radius: 1
                anchors.verticalCenter: parent.verticalCenter

                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: "#47DAFF" }
                    GradientStop { position: 1.0; color: "#7C5CFF" }
                }

                NumberAnimation on width {
                    running: true
                    from: 0
                    to: 230
                    duration: 2750
                    easing.type: Easing.InOutCubic
                }
            }
        }
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 34
        text: qsTr("CONNECTED  •  FOCUSED  •  READY")
        color: "#456173"
        font.pixelSize: 10
        font.weight: Font.Medium
        font.letterSpacing: 2
    }

    ParallelAnimation {
        running: true

        NumberAnimation {
            target: splashContent
            property: "opacity"
            from: 0
            to: 1
            duration: 850
            easing.type: Easing.OutCubic
        }

        NumberAnimation {
            target: splashContent
            property: "scale"
            from: 0.84
            to: 1
            duration: 950
            easing.type: Easing.OutBack
        }
    }

    Timer {
        interval: 3100
        running: true
        repeat: false
        onTriggered: exitAnimation.start()
    }

    ParallelAnimation {
        id: exitAnimation

        NumberAnimation {
            target: splashContent
            property: "opacity"
            to: 0
            duration: 420
            easing.type: Easing.InCubic
        }

        NumberAnimation {
            target: splashContent
            property: "scale"
            to: 1.08
            duration: 420
            easing.type: Easing.InCubic
        }

        onFinished: root.finished()// sent to main qml
    }
}
