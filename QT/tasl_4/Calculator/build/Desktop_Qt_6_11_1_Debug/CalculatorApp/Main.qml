import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window

    width: 440
    height: 650
    minimumWidth: 380
    minimumHeight: 580
    visible: true
    title: qsTr("Calculator")
    color: "#0B1118"

    FocusScope {
        id: calculatorUi
        anchors.fill: parent
        anchors.margins: 20
        focus: true

        Component.onCompleted: forceActiveFocus()

        Keys.onPressed: function(event) {
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                calculator.pressButton("=")
                event.accepted = true
            } else if (event.key === Qt.Key_Backspace
                       || event.key === Qt.Key_Delete) {
                calculator.pressButton("⌫")
                event.accepted = true
            } else if (event.key === Qt.Key_Escape) {
                calculator.pressButton("C")
                event.accepted = true
            } else if (event.text.length > 0) {
                calculator.pressButton(event.text)
                event.accepted = "0123456789.+-*/=%cC".indexOf(event.text) !== -1
            }
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 14

            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                Rectangle {
                    Layout.preferredWidth: 46
                    Layout.preferredHeight: 46
                    radius: 14
                    color: "#F2B84B"

                    Text {
                        anchors.centerIn: parent
                        text: "="
                        color: "#101820"
                        font.pixelSize: 25
                        font.weight: Font.Bold
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 1

                    Label {
                        text: qsTr("Calculator")
                        color: "#F4F6F8"
                        font.pixelSize: 25
                        font.weight: Font.DemiBold
                    }

                    Label {
                        text: qsTr("Fast • Simple • Accurate")
                        color: "#758999"
                        font.pixelSize: 12
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 145
                radius: 22
                color: "#111A24"
                border.color: "#22303D"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 5

                    Label {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: calculator.expression.length > 0
                              ? calculator.expression : qsTr("Ready")
                        color: "#687E8F"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignTop
                        elide: Text.ElideLeft
                    }

                    Label {
                        Layout.fillWidth: true
                        text: calculator.display
                        color: calculator.errorMessage.length > 0
                               ? "#FF8585" : "#F4F6F8"
                        font.pixelSize: Math.max(
                            30, 50 - Math.max(0, text.length - 9) * 2)
                        font.weight: Font.Light
                        horizontalAlignment: Text.AlignRight
                        elide: Text.ElideLeft
                    }

                    Label {
                        Layout.fillWidth: true
                        visible: calculator.errorMessage.length > 0
                        text: calculator.errorMessage
                        color: "#FF8585"
                        font.pixelSize: 11
                        horizontalAlignment: Text.AlignRight
                    }
                }
            }

            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 4
                columnSpacing: 10
                rowSpacing: 10

                Repeater {
                    model: [
                        { text: "C",  type: "utility" },
                        { text: "⌫", type: "utility" },
                        { text: "%",  type: "utility" },
                        { text: "÷",  type: "operator" },
                        { text: "7",  type: "number" },
                        { text: "8",  type: "number" },
                        { text: "9",  type: "number" },
                        { text: "×",  type: "operator" },
                        { text: "4",  type: "number" },
                        { text: "5",  type: "number" },
                        { text: "6",  type: "number" },
                        { text: "−",  type: "operator" },
                        { text: "1",  type: "number" },
                        { text: "2",  type: "number" },
                        { text: "3",  type: "number" },
                        { text: "+",  type: "operator" },
                        { text: "±",  type: "utility" },
                        { text: "0",  type: "number" },
                        { text: ".",  type: "number" },
                        { text: "=",  type: "equals" }
                    ]

                    Button {
                        id: calculatorButton
                        property var buttonData: modelData

                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.minimumHeight: 52
                        hoverEnabled: true

                        onClicked: {
                            calculator.pressButton(buttonData.text)
                            calculatorUi.forceActiveFocus()
                        }

                        contentItem: Text {
                            text: calculatorButton.buttonData.text
                            color: calculatorButton.buttonData.type === "equals"
                                   ? "#111820"
                                   : calculatorButton.buttonData.type === "operator"
                                     ? "#F2B84B" : "#EDF1F4"
                            font.pixelSize: 21
                            font.weight: Font.DemiBold
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 16
                            color: {
                                if (calculatorButton.buttonData.type === "equals")
                                    return calculatorButton.down ? "#C99A3D" : "#F2B84B"
                                if (calculatorButton.buttonData.type === "operator")
                                    return calculatorButton.down ? "#293744" : "#1C2934"
                                if (calculatorButton.buttonData.type === "utility")
                                    return calculatorButton.down ? "#26343F" : "#192631"
                                return calculatorButton.down ? "#21303B" : "#15212B"
                            }
                            border.color: calculatorButton.buttonData.type === "equals"
                                          ? "#F2B84B" : "#263541"
                        }
                    }
                }
            }

            Label {
                Layout.fillWidth: true
                text: qsTr("Use the buttons or your keyboard")
                color: "#536876"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
