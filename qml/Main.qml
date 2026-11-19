import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 360
    height: 640
    title: qsTr("Cuvinte")

    function addCurrentText() {
        if (wordModel.add(input.text))
            input.clear()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: input
                Layout.fillWidth: true
                placeholderText: qsTr("Scrie un cuvânt sau o frază")
                onAccepted: addCurrentText()
            }

            Button {
                text: qsTr("Adaugă")
                onClicked: addCurrentText()
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: wordModel

            // Grupare pe litere: la fiecare schimbare de literă apare un titlu.
            section.property: "letter"
            section.criteria: ViewSection.FullString
            section.delegate: Rectangle {
                required property string section
                width: listView.width
                height: 36
                color: palette.mid

                Label {
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    anchors.verticalCenter: parent.verticalCenter
                    text: parent.section
                    font.bold: true
                    font.pixelSize: 18
                }
            }

            delegate: ItemDelegate {
                width: listView.width
                text: model.display

                ToolButton {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: "✕"
                    onClicked: wordModel.remove(index)
                }
            }
        }
    }
}