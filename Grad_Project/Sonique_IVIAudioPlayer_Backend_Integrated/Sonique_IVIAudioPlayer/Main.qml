import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root

    width: 1280
    height: 720
    minimumWidth: 960
    minimumHeight: 640
    visible: true
    title: qsTr("Sonique IVI Audio")
    color: "#070B12"

    property bool splashActive: true

    StackView {
        id: navigationStack

        anchors.fill: parent
        opacity: root.splashActive ? 0.0 : 1.0

        initialItem: HomePage {
            onSourceRequested: function(sourceId, sourceTitle, accentColor, iconText) {
                navigationStack.push(sourcePageComponent, {
                    "sourceId": sourceId,
                    "pageTitle": sourceTitle,
                    "accentColor": accentColor,
                    "iconText": iconText
                })
            }
        }

        pushEnter: Transition {
            NumberAnimation {
                property: "x"
                from: navigationStack.width
                to: 0
                duration: 360
                easing.type: Easing.OutCubic
            }
            NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 280 }
        }

        pushExit: Transition {
            NumberAnimation {
                property: "x"
                from: 0
                to: -navigationStack.width * 0.12
                duration: 360
                easing.type: Easing.OutCubic
            }
            NumberAnimation { property: "opacity"; from: 1; to: 0.55; duration: 260 }
        }

        popEnter: Transition {
            NumberAnimation {
                property: "x"
                from: -navigationStack.width * 0.12
                to: 0
                duration: 330
                easing.type: Easing.OutCubic
            }
            NumberAnimation { property: "opacity"; from: 0.55; to: 1; duration: 260 }
        }

        popExit: Transition {
            NumberAnimation {
                property: "x"
                from: 0
                to: navigationStack.width
                duration: 330
                easing.type: Easing.OutCubic
            }
            NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 240 }
        }

        Behavior on opacity {
            NumberAnimation { duration: 500; easing.type: Easing.OutCubic }
        }
    }

    Component {
        id: sourcePageComponent

        SourcePage {
            playbackEngine: soniquePlaybackEngine

            onBackRequested: {
                playbackEngine.stopPlayback()
                navigationStack.pop()
            }
        }
    }

    SplashScreen {
        id: splash

        anchors.fill: parent
        z: 100
        visible: root.splashActive

        onFinished: root.splashActive = false


    }
}
