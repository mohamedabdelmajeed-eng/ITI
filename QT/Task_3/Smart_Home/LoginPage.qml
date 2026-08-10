import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Page {
    id: root

    // =========================================================
    // References from Main.qml
    // =========================================================

    required property var appWindow
    required property var navigationStack


    // =========================================================
    // Login state
    // =========================================================

    property bool loginInProgress: false
    property string errorMessage: ""
    property bool rememberMe: false


    // =========================================================
    // Page background
    // =========================================================

    background: Rectangle {
        color: appWindow.backgroundColor
    }


    // =========================================================
    // Login background image
    // =========================================================

    Image {
        id: backgroundImage

        anchors.fill: parent

        // New background image
        source: "qrc:/Images/logInbackground.png"

        fillMode: Image.PreserveAspectCrop

        smooth: true
        asynchronous: true
    }


    // =========================================================
    // Dark cinematic overlay
    // =========================================================

    Rectangle {
        anchors.fill: parent

        color: "#050608"

        // Allows the house to remain visible
        // while keeping text readable.
        opacity: 0.50
    }


    // =========================================================
    // Outer premium gold border
    // =========================================================

    Rectangle {
        anchors.fill: parent
        anchors.margins: 15

        radius: 28

        color: "transparent"

        border.color: "#A97827"
        border.width: 1
    }


    // =========================================================
    // MAIN LAYOUT
    // =========================================================

    RowLayout {
        id: mainLayout

        anchors.fill: parent

        anchors.leftMargin: 45
        anchors.rightMargin: 45

        anchors.topMargin: 38
        anchors.bottomMargin: 38

        spacing: 45


        // =====================================================
        // LEFT BRANDING AREA
        // =====================================================

        Item {
            id: brandingArea

            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.preferredWidth: 1.40


            // =================================================
            // Brand content
            // =================================================

            ColumnLayout {
                id: brandColumn

                // Correct position:
                // Keep logo and branding inside the left side.
                anchors.left: parent.left
                anchors.leftMargin: 70

                // Slightly above vertical center looks
                // better than exact center.
                anchors.verticalCenter: parent.verticalCenter

                anchors.verticalCenterOffset: -25

                width: Math.min(
                           brandingArea.width * 0.52,
                           430
                       )

                spacing: 12


                // =============================================
                // LOGO AREA
                // =============================================

                Item {
                    id: logoContainer

                    Layout.fillWidth: true

                    Layout.preferredHeight:
                        Math.min(
                            250,
                            brandingArea.height * 0.30
                        )


                    Image {
                        id: logoImage

                        anchors.centerIn: parent

                        // Responsive but controlled size.
                        width:
                            Math.min(
                                logoContainer.width * 0.78,
                                300
                            )

                        height:
                            Math.min(
                                logoContainer.height * 0.95,
                                235
                            )

                        // Exact logo path requested
                        source:
                            "qrc:/Images/Logo_.png"

                        fillMode:
                            Image.PreserveAspectFit

                        smooth: true
                        asynchronous: true
                    }
                }


                // =============================================
                // Brand tagline
                // =============================================

                Label {
                    Layout.fillWidth: true

                    text:
                        qsTr(
                            "LIVE SMART, LIVE BETTER"
                        )

                    color:
                        appWindow.brightGoldColor

                    font.pixelSize: 14
                    font.bold: true

                    font.letterSpacing: 3

                    horizontalAlignment:
                        Text.AlignHCenter
                }


                // =============================================
                // Decorative separator
                // =============================================

                RowLayout {
                    Layout.alignment:
                        Qt.AlignHCenter

                    spacing: 8


                    Rectangle {
                        Layout.preferredWidth: 48
                        Layout.preferredHeight: 1

                        color:
                            appWindow.goldColor
                    }


                    Label {
                        text: "◇"

                        color:
                            appWindow.brightGoldColor

                        font.pixelSize: 12
                    }


                    Rectangle {
                        Layout.preferredWidth: 48
                        Layout.preferredHeight: 1

                        color:
                            appWindow.goldColor
                    }
                }


                // =============================================
                // Welcome message
                // =============================================

                Label {
                    Layout.fillWidth: true

                    text:
                        qsTr(
                            "Good evening, everything is under control."
                        )

                    color:
                        appWindow.mainTextColor

                    font.pixelSize: 18
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter

                    wrapMode:
                        Text.WordWrap
                }


                // =============================================
                // Small description
                // =============================================

                Label {
                    Layout.fillWidth: true

                    text:
                        qsTr(
                            "Secure access to your smart home."
                        )

                    color:
                        appWindow.secondaryTextColor

                    font.pixelSize: 11

                    horizontalAlignment:
                        Text.AlignHCenter

                    wrapMode:
                        Text.WordWrap
                }
            }
        }


        // =====================================================
        // RIGHT LOGIN PANEL
        // =====================================================

        Rectangle {
            id: loginPanel

            Layout.preferredWidth: 420
            Layout.minimumWidth: 390
            Layout.maximumWidth: 440

            Layout.preferredHeight:
                Math.min(
                    610,
                    root.height - 100
                )

            Layout.alignment:
                Qt.AlignVCenter

            radius: 28

            color: "#F0101113"

            border.color: "#A97827"
            border.width: 1


            // =================================================
            // Inner border
            // =================================================

            Rectangle {
                anchors.fill: parent
                anchors.margins: 7

                radius: 22

                color: "transparent"

                border.color: "#332A1B"
                border.width: 1
            }


            // =================================================
            // Login content
            // =================================================

            ColumnLayout {
                anchors.fill: parent

                anchors.leftMargin: 30
                anchors.rightMargin: 30

                anchors.topMargin: 30
                anchors.bottomMargin: 30

                spacing: 13


                // =============================================
                // Welcome title
                // =============================================

                Label {
                    Layout.fillWidth: true

                    text:
                        qsTr("Welcome Back")

                    color:
                        appWindow.mainTextColor

                    font.pixelSize: 28
                    font.bold: true

                    horizontalAlignment:
                        Text.AlignHCenter
                }


                Label {
                    Layout.fillWidth: true

                    text:
                        qsTr(
                            "Sign in to continue"
                        )

                    color:
                        appWindow.secondaryTextColor

                    font.pixelSize: 12

                    horizontalAlignment:
                        Text.AlignHCenter
                }


                // =============================================
                // Gold separator
                // =============================================

                RowLayout {
                    Layout.fillWidth: true

                    Layout.topMargin: 3
                    Layout.bottomMargin: 8

                    spacing: 8


                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1

                        color: "#514022"
                    }


                    Label {
                        text: "◇"

                        color:
                            appWindow.goldColor

                        font.pixelSize: 14
                    }


                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1

                        color: "#514022"
                    }
                }


                // =============================================
                // Username
                // =============================================

                TextField {
                    id: usernameField

                    Layout.fillWidth: true
                    Layout.preferredHeight: 54

                    placeholderText:
                        qsTr("Username")

                    color:
                        appWindow.mainTextColor

                    placeholderTextColor:
                        "#85858C"

                    font.pixelSize: 13

                    enabled:
                        !root.loginInProgress

                    leftPadding: 18
                    rightPadding: 18


                    background: Rectangle {
                        radius: 13

                        color:
                            usernameField.activeFocus
                            ? "#1A1B1E"
                            : "#151619"

                        border.color:
                            usernameField.activeFocus
                            ? appWindow.brightGoldColor
                            : "#3A3B3F"

                        border.width:
                            usernameField.activeFocus
                            ? 1.5
                            : 1


                        Behavior on border.color {
                            ColorAnimation {
                                duration: 130
                            }
                        }
                    }
                }


                // =============================================
                // Password
                // =============================================

                TextField {
                    id: passwordField

                    Layout.fillWidth: true
                    Layout.preferredHeight: 54

                    placeholderText:
                        qsTr("Password")

                    echoMode:
                        TextInput.Password

                    color:
                        appWindow.mainTextColor

                    placeholderTextColor:
                        "#85858C"

                    font.pixelSize: 13

                    enabled:
                        !root.loginInProgress

                    leftPadding: 18
                    rightPadding: 18


                    background: Rectangle {
                        radius: 13

                        color:
                            passwordField.activeFocus
                            ? "#1A1B1E"
                            : "#151619"

                        border.color:
                            passwordField.activeFocus
                            ? appWindow.brightGoldColor
                            : "#3A3B3F"

                        border.width:
                            passwordField.activeFocus
                            ? 1.5
                            : 1


                        Behavior on border.color {
                            ColorAnimation {
                                duration: 130
                            }
                        }
                    }


                    Keys.onReturnPressed: {
                        root.attemptLogin()
                    }
                }


                // =============================================
                // REMEMBER ME + FORGOT PASSWORD
                // =============================================

                RowLayout {
                    id: optionsRow

                    Layout.fillWidth: true
                    Layout.preferredHeight: 32

                    spacing: 10


                    // =========================================
                    // Custom Remember Me
                    // =========================================

                    RowLayout {
                        spacing: 8


                        CheckBox {
                            id: rememberCheckBox

                            Layout.preferredWidth: 22
                            Layout.preferredHeight: 22

                            checked:
                                root.rememberMe


                            onToggled: {

                                root.rememberMe =
                                        checked

                                console.log(
                                    "Remember me:",
                                    checked
                                )
                            }


                            // =================================
                            // Premium custom checkbox
                            // =================================

                            indicator: Rectangle {
                                width: 20
                                height: 20

                                x: 1
                                y: 1

                                radius: 5

                                color:
                                    rememberCheckBox.checked
                                    ? appWindow.goldColor
                                    : "#191A1D"

                                border.color:
                                    rememberCheckBox.checked
                                    ? appWindow.brightGoldColor
                                    : "#57585C"

                                border.width: 1


                                Label {
                                    anchors.centerIn:
                                        parent

                                    visible:
                                        rememberCheckBox.checked

                                    text: "✓"

                                    color: "#17120A"

                                    font.pixelSize: 12
                                    font.bold: true
                                }
                            }


                            // Remove the default CheckBox text.
                            contentItem: Item {
                                implicitWidth: 0
                                implicitHeight: 0
                            }
                        }


                        Label {
                            text:
                                qsTr("Remember me")

                            color:
                                appWindow.secondaryTextColor

                            font.pixelSize: 11

                            verticalAlignment:
                                Text.AlignVCenter

                            Layout.alignment:
                                Qt.AlignVCenter
                        }
                    }


                    // Push Forgot Password to the right.
                    Item {
                        Layout.fillWidth: true
                    }


                    Button {
                        id: forgotPasswordButton

                        flat: true

                        hoverEnabled: true

                        Layout.preferredHeight: 30

                        text:
                            qsTr(
                                "Forgot Password?"
                            )


                        onClicked: {
                            console.log(
                                "Forgot Password clicked"
                            )
                        }


                        background: Item {
                        }


                        contentItem: Text {
                            text:
                                forgotPasswordButton.text

                            color:
                                forgotPasswordButton.hovered
                                ? appWindow.brightGoldColor
                                : appWindow.goldColor

                            font.pixelSize: 11
                            font.bold: true

                            horizontalAlignment:
                                Text.AlignRight

                            verticalAlignment:
                                Text.AlignVCenter


                            Behavior on color {
                                ColorAnimation {
                                    duration: 120
                                }
                            }
                        }
                    }
                }


                // =============================================
                // Error message
                // =============================================

                Label {
                    Layout.fillWidth: true

                    text:
                        root.errorMessage

                    visible:
                        root.errorMessage !== ""

                    color:
                        appWindow.errorColor

                    font.pixelSize: 11

                    horizontalAlignment:
                        Text.AlignHCenter

                    wrapMode:
                        Text.WordWrap
                }


                // =============================================
                // SIGN IN BUTTON
                // =============================================

                Button {
                    id: loginButton

                    Layout.fillWidth: true
                    Layout.preferredHeight: 56

                    enabled:
                        !root.loginInProgress

                    hoverEnabled: true


                    onClicked: {
                        root.attemptLogin()
                    }


                    background: Rectangle {
                        radius: 14

                        color:
                            !loginButton.enabled
                            ? "#786336"
                            : loginButton.down
                              ? "#B77E22"
                              : loginButton.hovered
                                ? "#F1C55D"
                                : "#D9A63D"

                        border.color:
                            "#F3CE78"

                        border.width: 1


                        Behavior on color {
                            ColorAnimation {
                                duration: 140
                            }
                        }
                    }


                    contentItem: RowLayout {
                        spacing: 12


                        Item {
                            Layout.fillWidth: true
                        }


                        Label {
                            text: "‹"

                            color: "#181309"

                            font.pixelSize: 21
                        }


                        Label {
                            text:
                                qsTr("SIGN IN")

                            color: "#181309"

                            font.pixelSize: 14
                            font.bold: true

                            font.letterSpacing: 4
                        }


                        Label {
                            text: "›"

                            color: "#181309"

                            font.pixelSize: 21
                        }


                        Item {
                            Layout.fillWidth: true
                        }
                    }
                }


                // =============================================
                // Busy indicator
                // =============================================

                BusyIndicator {
                    Layout.alignment:
                        Qt.AlignHCenter

                    width: 34
                    height: 34

                    running:
                        root.loginInProgress

                    visible:
                        root.loginInProgress
                }


                Label {
                    Layout.fillWidth: true

                    text:
                        qsTr(
                            "Connecting to your smart home..."
                        )

                    visible:
                        root.loginInProgress

                    color:
                        appWindow.goldColor

                    font.pixelSize: 10

                    horizontalAlignment:
                        Text.AlignHCenter
                }


                // =============================================
                // OR
                // =============================================

                RowLayout {
                    Layout.fillWidth: true

                    spacing: 8


                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1

                        color: "#333438"
                    }


                    Label {
                        text:
                            qsTr("OR")

                        color:
                            appWindow.secondaryTextColor

                        font.pixelSize: 9
                    }


                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1

                        color: "#333438"
                    }
                }


                // =============================================
                // FINGERPRINT BUTTON
                // =============================================

                Button {
                    id: fingerprintButton

                    Layout.fillWidth: true
                    Layout.preferredHeight: 50

                    hoverEnabled: true


                    onClicked: {

                        console.log(
                            "Fingerprint login simulated"
                        )
                    }


                    background: Rectangle {
                        radius: 13

                        color:
                            fingerprintButton.down
                            ? "#202125"
                            : fingerprintButton.hovered
                              ? "#1D1E21"
                              : "#151619"

                        border.color:
                            fingerprintButton.hovered
                            ? appWindow.goldColor
                            : "#514327"

                        border.width: 1
                    }


                    contentItem: RowLayout {
                        spacing: 10


                        Item {
                            Layout.fillWidth: true
                        }


                        Label {
                            text: "◉"

                            color:
                                appWindow.brightGoldColor

                            font.pixelSize: 18
                        }


                        Label {
                            text:
                                qsTr(
                                    "SIGN IN WITH FINGERPRINT"
                                )

                            color:
                                appWindow.mainTextColor

                            font.pixelSize: 9
                            font.bold: true

                            font.letterSpacing: 1.2
                        }


                        Label {
                            text: "›"

                            color:
                                appWindow.goldColor

                            font.pixelSize: 19
                        }


                        Item {
                            Layout.fillWidth: true
                        }
                    }
                }


                // Keeps all controls near the top
                // instead of stretching them vertically.
                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }


    // =========================================================
    // LOGIN FUNCTION
    // =========================================================

    function attemptLogin() {

        // Clear old errors.
        root.errorMessage = ""


        // Check username and password.
        if (usernameField.text.trim() === "" ||
            passwordField.text.trim() === "") {

            root.errorMessage =
                    qsTr(
                        "Please enter username and password."
                    )

            console.log(
                "Login failed: empty input"
            )

            return
        }


        // Start loading.
        root.loginInProgress = true


        console.log(
            "Login started:",
            usernameField.text
        )


        loginTimer.restart()
    }


    // =========================================================
    // TWO SECOND LOGIN SIMULATION
    // =========================================================

    Timer {
        id: loginTimer

        interval: 2000
        repeat: false


        onTriggered: {

            root.loginInProgress = false


            console.log(
                "Login successful:",
                usernameField.text
            )


            navigationStack.push(
                Qt.resolvedUrl(
                    "DashboardPage.qml"
                ),
                {
                    "appWindow":
                        appWindow,

                    "navigationStack":
                        navigationStack
                }
            )
        }
    }
}