import QtQuick
import QtQuick.Controls


ApplicationWindow {
    id: root

    // =========================================================
    // Main Window
    // =========================================================

    width: 1200
    height: 800

    minimumWidth: 900
    minimumHeight: 650

    visible: true

    // English is the source/default language.
    // Later Qt Linguist can translate this.
    title: qsTr("Elsheikh Smart Homes")

    color: backgroundColor


    // =========================================================
    // Global Premium Theme Colors
    // =========================================================

    // Main application background.
    property color backgroundColor: "#07090B"

    // Main card color.
    property color cardColor: "#131416"

    // Slightly lighter card color.
    property color elevatedCardColor: "#1A1B1E"

    // Main premium gold.
    property color goldColor: "#D6A443"

    // Bright gold for important information.
    property color brightGoldColor: "#F2CA6B"

    // Darker gold for pressed buttons.
    property color softGoldColor: "#A97826"

    // Main text.
    property color mainTextColor: "#F6F2E9"

    // Secondary descriptions.
    property color secondaryTextColor: "#AAA399"

    // Error messages.
    property color errorColor: "#E86A6A"

    // Green can be used for successful/device-active state.
    property color activeColor: "#D6A443"


    // =========================================================
    // Main Navigation
    // =========================================================

    StackView {
        id: stackView

        anchors.fill: parent

        // Login is the first page.
        initialItem: LoginPage {

            // Give LoginPage access to the theme.
            appWindow: root

            // Give LoginPage access to StackView.
            navigationStack: stackView
        }
    }
}