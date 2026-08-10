import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Page {
    id: root

    // =========================================================
    // References received from DashboardPage
    // =========================================================

    required property var appWindow
    required property var navigationStack


    // =========================================================
    // Settings values
    // =========================================================

    property int brightnessValue: 70
    property int temperatureValue: 24
    property bool notificationsEnabled: true


    // =========================================================
    // Main background
    // =========================================================

    background: Rectangle {
        color: appWindow.backgroundColor
    }


    // =========================================================
    // ScrollView
    // =========================================================

    ScrollView {
        id: settingsScroll

        anchors.fill: parent

        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff


        ColumnLayout {
            width: settingsScroll.availableWidth

            spacing: 24


            // =================================================
            // HEADER
            // =================================================

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 145

                color: "#111214"

                border.color: "#4D3D22"
                border.width: 1


                RowLayout {
                    anchors.fill: parent

                    anchors.leftMargin: 35
                    anchors.rightMargin: 35
                    anchors.topMargin: 25
                    anchors.bottomMargin: 25

                    spacing: 22


                    // =========================================
                    // Back button
                    // =========================================

                    Button {
                        id: backButton

                        Layout.preferredWidth: 115
                        Layout.preferredHeight: 48

                        text: qsTr("Back")

                        hoverEnabled: true


                        onClicked: {
                            navigationStack.pop()
                        }


                        background: Rectangle {
                            radius: 14

                            color:
                                backButton.down
                                ? "#29271F"
                                : backButton.hovered
                                  ? "#211E17"
                                  : "#171719"

                            border.color:
                                appWindow.goldColor

                            border.width: 1


                            Behavior on color {
                                ColorAnimation {
                                    duration: 140
                                }
                            }
                        }


                        contentItem: RowLayout {
                            spacing: 8

                            Item {
                                Layout.fillWidth: true
                            }


                            Label {
                                text: "‹"

                                color:
                                    appWindow.brightGoldColor

                                font.pixelSize: 25
                            }


                            Label {
                                text: backButton.text

                                color:
                                    appWindow.mainTextColor

                                font.pixelSize: 14
                                font.bold: true
                            }


                            Item {
                                Layout.fillWidth: true
                            }
                        }
                    }


                    // =========================================
                    // Page title
                    // =========================================

                    ColumnLayout {
                        Layout.fillWidth: true

                        spacing: 4


                        Label {
                            text: qsTr("Settings")

                            color:
                                appWindow.mainTextColor

                            font.pixelSize: 32
                            font.bold: true
                        }


                        Label {
                            text:
                                qsTr(
                                    "Personalize your smart home experience"
                                )

                            color:
                                appWindow.secondaryTextColor

                            font.pixelSize: 14
                        }
                    }


                    // =========================================
                    // Decorative settings badge
                    // =========================================

                    Rectangle {
                        Layout.preferredWidth: 58
                        Layout.preferredHeight: 58

                        radius: 29

                        color: "#29220F"

                        border.color:
                            appWindow.goldColor

                        border.width: 1


                        Label {
                            anchors.centerIn: parent

                            text: "⚙"

                            color:
                                appWindow.brightGoldColor

                            font.pixelSize: 28
                        }
                    }
                }
            }


            // =================================================
            // MAIN SETTINGS AREA
            // =================================================

            GridLayout {
                Layout.fillWidth: true

                Layout.leftMargin: 70
                Layout.rightMargin: 70

                columns: 2

                columnSpacing: 20
                rowSpacing: 20


                // =================================================
                // LANGUAGE CARD
                // =================================================

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 235

                    radius: 24

                    color: "#141416"

                    border.color: "#5C4828"
                    border.width: 1


                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 25

                        spacing: 12


                        RowLayout {
                            Layout.fillWidth: true

                            spacing: 12


                            Rectangle {
                                Layout.preferredWidth: 48
                                Layout.preferredHeight: 48

                                radius: 15

                                color: "#29220F"

                                border.color:
                                    appWindow.goldColor

                                border.width: 1


                                Label {
                                    anchors.centerIn: parent

                                    text: "文"

                                    color:
                                        appWindow.brightGoldColor

                                    font.pixelSize: 22
                                    font.bold: true
                                }
                            }


                            ColumnLayout {
                                Layout.fillWidth: true

                                spacing: 2


                                Label {
                                    text: qsTr("Language")

                                    color:
                                        appWindow.mainTextColor

                                    font.pixelSize: 19
                                    font.bold: true
                                }


                                Label {
                                    text:
                                        qsTr(
                                            "Choose the application language"
                                        )

                                    color:
                                        appWindow.secondaryTextColor

                                    font.pixelSize: 12
                                }
                            }
                        }


                        Item {
                            Layout.preferredHeight: 5
                        }


                        // =========================================
                        // Language ComboBox
                        // =========================================

                        ComboBox {
                            id: languageCombo

                            Layout.fillWidth: true
                            Layout.preferredHeight: 55

                            model: [
                                "English",
                                "العربية"
                            ]

                            currentIndex:
                                Qt.uiLanguage === "ar"
                                ? 1
                                : 0


                            onActivated: function(index) {

                                console.log(
                                    "Language selected:",
                                    currentText
                                )
                            }


                            contentItem: Text {
                                leftPadding: 18

                                text:
                                    languageCombo.displayText

                                color:
                                    appWindow.mainTextColor

                                font.pixelSize: 14

                                verticalAlignment:
                                    Text.AlignVCenter

                                elide:
                                    Text.ElideRight
                            }


                            background: Rectangle {
                                radius: 14

                                color: "#1B1C1F"

                                border.color:
                                    languageCombo.activeFocus
                                    ? appWindow.goldColor
                                    : "#3F3F43"

                                border.width:
                                    languageCombo.activeFocus
                                    ? 2
                                    : 1
                            }


                            indicator: Label {
                                x:
                                    languageCombo.width
                                    - width
                                    - 18

                                y:
                                    languageCombo.height / 2
                                    - height / 2

                                text: "⌄"

                                color:
                                    appWindow.goldColor

                                font.pixelSize: 20
                            }
                        }
                    }
                }


                // =================================================
                // BRIGHTNESS CARD
                // =================================================

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 235

                    radius: 24

                    color: "#141416"

                    border.color: "#5C4828"
                    border.width: 1


                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 25

                        spacing: 12


                        RowLayout {
                            Layout.fillWidth: true

                            spacing: 12


                            Rectangle {
                                Layout.preferredWidth: 48
                                Layout.preferredHeight: 48

                                radius: 15

                                color: "#29220F"

                                border.color:
                                    appWindow.goldColor

                                border.width: 1


                                Label {
                                    anchors.centerIn: parent

                                    text: "☀"

                                    color:
                                        appWindow.brightGoldColor

                                    font.pixelSize: 24
                                }
                            }


                            ColumnLayout {
                                Layout.fillWidth: true

                                spacing: 2


                                Label {
                                    text:
                                        qsTr("Screen Brightness")

                                    color:
                                        appWindow.mainTextColor

                                    font.pixelSize: 19
                                    font.bold: true
                                }


                                Label {
                                    text:
                                        qsTr(
                                            "Adjust the simulated screen brightness"
                                        )

                                    color:
                                        appWindow.secondaryTextColor

                                    font.pixelSize: 12
                                }
                            }


                            Label {
                                text:
                                    Math.round(
                                        brightnessSlider.value
                                    ) + "%"

                                color:
                                    appWindow.brightGoldColor

                                font.pixelSize: 20
                                font.bold: true
                            }
                        }


                        Item {
                            Layout.preferredHeight: 15
                        }


                        Slider {
                            id: brightnessSlider

                            Layout.fillWidth: true
                            Layout.preferredHeight: 35

                            from: 0
                            to: 100

                            value:
                                root.brightnessValue

                            stepSize: 1


                            onMoved: {

                                root.brightnessValue =
                                        Math.round(value)

                                console.log(
                                    "Brightness:",
                                    root.brightnessValue
                                )
                            }


                            background: Rectangle {
                                x:
                                    brightnessSlider.leftPadding

                                y:
                                    brightnessSlider.topPadding
                                    + brightnessSlider.availableHeight
                                      / 2
                                    - height / 2

                                width:
                                    brightnessSlider.availableWidth

                                height: 7

                                radius: 4

                                color: "#35363A"


                                Rectangle {
                                    width:
                                        brightnessSlider.visualPosition
                                        * parent.width

                                    height:
                                        parent.height

                                    radius:
                                        parent.radius

                                    color:
                                        appWindow.goldColor
                                }
                            }


                            handle: Rectangle {
                                x:
                                    brightnessSlider.leftPadding
                                    + brightnessSlider.visualPosition
                                      * (
                                          brightnessSlider.availableWidth
                                          - width
                                        )

                                y:
                                    brightnessSlider.topPadding
                                    + brightnessSlider.availableHeight
                                      / 2
                                    - height / 2

                                width: 24
                                height: 24

                                radius: 12

                                color: "#F4F1E9"

                                border.color:
                                    appWindow.brightGoldColor

                                border.width: 2
                            }
                        }


                        RowLayout {
                            Layout.fillWidth: true


                            Label {
                                text: "0%"

                                color:
                                    appWindow.secondaryTextColor

                                font.pixelSize: 10
                            }


                            Item {
                                Layout.fillWidth: true
                            }


                            Label {
                                text: "100%"

                                color:
                                    appWindow.secondaryTextColor

                                font.pixelSize: 10
                            }
                        }
                    }
                }


                // =================================================
                // TEMPERATURE CARD
                // =================================================

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 330

                    radius: 24

                    color: "#141416"

                    border.color: "#5C4828"
                    border.width: 1


                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 25

                        spacing: 12


                        RowLayout {
                            Layout.fillWidth: true

                            spacing: 12


                            Rectangle {
                                Layout.preferredWidth: 48
                                Layout.preferredHeight: 48

                                radius: 15

                                color: "#29220F"

                                border.color:
                                    appWindow.goldColor

                                border.width: 1


                                Label {
                                    anchors.centerIn: parent

                                    text: "♨"

                                    color:
                                        appWindow.brightGoldColor

                                    font.pixelSize: 24
                                }
                            }


                            ColumnLayout {
                                Layout.fillWidth: true


                                Label {
                                    text:
                                        qsTr("Room Temperature")

                                    color:
                                        appWindow.mainTextColor

                                    font.pixelSize: 19
                                    font.bold: true
                                }


                                Label {
                                    text:
                                        qsTr(
                                            "Choose your preferred temperature"
                                        )

                                    color:
                                        appWindow.secondaryTextColor

                                    font.pixelSize: 12
                                }
                            }
                        }


                        RowLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            spacing: 30


                            Dial {
                                id: temperatureDial

                                Layout.preferredWidth: 175
                                Layout.preferredHeight: 175

                                from: 16
                                to: 30

                                value:
                                    root.temperatureValue

                                stepSize: 1


                                onMoved: {

                                    root.temperatureValue =
                                            Math.round(value)

                                    console.log(
                                        "Temperature:",
                                        root.temperatureValue
                                    )
                                }


                                background: Rectangle {
                                    x: 10
                                    y: 10

                                    width:
                                        temperatureDial.width - 20

                                    height:
                                        temperatureDial.height - 20

                                    radius: width / 2

                                    color: "#1A1B1E"

                                    border.color:
                                        "#725627"

                                    border.width: 2


                                    Rectangle {
                                        anchors.centerIn:
                                            parent

                                        width:
                                            parent.width - 28

                                        height:
                                            parent.height - 28

                                        radius: width / 2

                                        color: "#101113"

                                        border.color:
                                            "#3A3B3F"

                                        border.width: 1
                                    }


                                    Label {
                                        anchors.centerIn:
                                            parent

                                        text:
                                            Math.round(
                                                temperatureDial.value
                                            ) + "°C"

                                        color:
                                            appWindow.brightGoldColor

                                        font.pixelSize: 27
                                        font.bold: true
                                    }
                                }


                                handle: Rectangle {
                                    id: dialHandle

                                    width: 24
                                    height: 24

                                    radius: 12

                                    color:
                                        appWindow.brightGoldColor

                                    border.color: "#FFF0B4"
                                    border.width: 2

                                    x:
                                        temperatureDial.background.x
                                        + temperatureDial.background.width
                                          / 2
                                        - width / 2
                                        + Math.cos(
                                            temperatureDial.angle
                                            * Math.PI / 180
                                          )
                                          * (
                                              temperatureDial.background.width
                                              / 2
                                              - 20
                                            )

                                    y:
                                        temperatureDial.background.y
                                        + temperatureDial.background.height
                                          / 2
                                        - height / 2
                                        + Math.sin(
                                            temperatureDial.angle
                                            * Math.PI / 180
                                          )
                                          * (
                                              temperatureDial.background.height
                                              / 2
                                              - 20
                                            )
                                }
                            }


                            ColumnLayout {
                                Layout.fillWidth: true

                                spacing: 7


                                Label {
                                    text:
                                        qsTr(
                                            "Selected Temperature"
                                        )

                                    color:
                                        appWindow.secondaryTextColor

                                    font.pixelSize: 12
                                }


                                Label {
                                    text:
                                        root.temperatureValue
                                        + "°C"

                                    color:
                                        appWindow.brightGoldColor

                                    font.pixelSize: 34
                                    font.bold: true
                                }


                                Label {
                                    text:
                                        qsTr("Comfort range")

                                    color:
                                        appWindow.mainTextColor

                                    font.pixelSize: 13
                                }


                                Label {
                                    text: "16°C — 30°C"

                                    color:
                                        appWindow.secondaryTextColor

                                    font.pixelSize: 12
                                }
                            }
                        }
                    }
                }


                // =================================================
                // NOTIFICATIONS CARD
                // =================================================

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 330

                    radius: 24

                    color: "#141416"

                    border.color: "#5C4828"
                    border.width: 1


                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 25

                        spacing: 16


                        RowLayout {
                            Layout.fillWidth: true

                            spacing: 12


                            Rectangle {
                                Layout.preferredWidth: 48
                                Layout.preferredHeight: 48

                                radius: 15

                                color: "#29220F"

                                border.color:
                                    appWindow.goldColor

                                border.width: 1


                                Label {
                                    anchors.centerIn: parent

                                    text: "♢"

                                    color:
                                        appWindow.brightGoldColor

                                    font.pixelSize: 24
                                }
                            }


                            ColumnLayout {
                                Layout.fillWidth: true


                                Label {
                                    text:
                                        qsTr("Notifications")

                                    color:
                                        appWindow.mainTextColor

                                    font.pixelSize: 19
                                    font.bold: true
                                }


                                Label {
                                    text:
                                        qsTr(
                                            "Control smart home alerts"
                                        )

                                    color:
                                        appWindow.secondaryTextColor

                                    font.pixelSize: 12
                                }
                            }
                        }


                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 105

                            radius: 18

                            color: "#191A1D"

                            border.color: "#3F3F43"
                            border.width: 1


                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 20

                                spacing: 15


                                ColumnLayout {
                                    Layout.fillWidth: true


                                    Label {
                                        text:
                                            qsTr(
                                                "Enable Notifications"
                                            )

                                        color:
                                            appWindow.mainTextColor

                                        font.pixelSize: 15
                                        font.bold: true
                                    }


                                    Label {
                                        text:
                                            notificationsEnabled
                                            ? qsTr(
                                                "Smart alerts are enabled"
                                              )
                                            : qsTr(
                                                "Smart alerts are disabled"
                                              )

                                        color:
                                            appWindow.secondaryTextColor

                                        font.pixelSize: 11
                                    }
                                }


                                CheckBox {
                                    id: notificationsCheckBox

                                    checked:
                                        root.notificationsEnabled


                                    onToggled: {

                                        root.notificationsEnabled =
                                                checked

                                        console.log(
                                            "Notifications:",
                                            checked
                                        )
                                    }


                                    indicator: Rectangle {
                                        implicitWidth: 30
                                        implicitHeight: 30

                                        radius: 9

                                        color:
                                            notificationsCheckBox.checked
                                            ? appWindow.goldColor
                                            : "#242529"

                                        border.color:
                                            notificationsCheckBox.checked
                                            ? appWindow.brightGoldColor
                                            : "#55565B"

                                        border.width: 1


                                        Label {
                                            anchors.centerIn:
                                                parent

                                            visible:
                                                notificationsCheckBox.checked

                                            text: "✓"

                                            color: "#111214"

                                            font.pixelSize: 18
                                            font.bold: true
                                        }
                                    }
                                }
                            }
                        }


                        Item {
                            Layout.fillHeight: true
                        }


                        Label {
                            Layout.fillWidth: true

                            text:
                                qsTr(
                                    "Notifications are simulated using console output."
                                )

                            color:
                                appWindow.secondaryTextColor

                            font.pixelSize: 11

                            wrapMode: Text.WordWrap
                        }
                    }
                }
            }


            // =================================================
            // SAVE BUTTON AREA
            // =================================================

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 115

                Layout.leftMargin: 70
                Layout.rightMargin: 70
                Layout.bottomMargin: 35

                radius: 24

                color: "#131416"

                border.color: "#594727"
                border.width: 1


                Button {
                    id: saveButton

                    anchors.fill: parent
                    anchors.margins: 23

                    hoverEnabled: true

                    text: qsTr("SAVE SETTINGS")


                    onClicked: {

                        console.log(
                            "========== SETTINGS =========="
                        )

                        console.log(
                            "Language:",
                            languageCombo.currentText
                        )

                        // =====================================
                        // Apply selected application language
                        // =====================================

                        if (languageCombo.currentIndex === 0) {

                            Qt.uiLanguage = "en"

                            console.log(
                                "Application language changed to English"
                            )

                        } else {

                            Qt.uiLanguage = "ar"

                            console.log(
                                "Application language changed to Arabic"
                            )
                        }


                        console.log(
                            "Brightness:",
                            root.brightnessValue
                        )

                        console.log(
                            "Temperature:",
                            root.temperatureValue
                        )

                        console.log(
                            "Notifications:",
                            root.notificationsEnabled
                        )

                        console.log(
                            "Settings saved successfully"
                        )
                    }


                    background: Rectangle {
                        radius: 16

                        color:
                            saveButton.down
                            ? "#B17D26"
                            : saveButton.hovered
                              ? appWindow.brightGoldColor
                              : appWindow.goldColor

                        border.color: "#F0CC72"
                        border.width: 1


                        Behavior on color {
                            ColorAnimation {
                                duration: 150
                            }
                        }
                    }


                    contentItem: RowLayout {
                        spacing: 14


                        Item {
                            Layout.fillWidth: true
                        }


                        Label {
                            text: "◇"

                            color: "#17130A"

                            font.pixelSize: 22
                        }


                        Label {
                            text: saveButton.text

                            color: "#17130A"

                            font.pixelSize: 16
                            font.bold: true

                            font.letterSpacing: 3
                        }


                        Label {
                            text: "›"

                            color: "#17130A"

                            font.pixelSize: 26
                        }


                        Item {
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }
}