import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    // Meniul care apare când apeși pe un element
    Dialog {
        id: actionDialog
        property int row: -1
        property string word: ""

        parent: Overlay.overlay
        anchors.centerIn: parent
        width: Math.min(parent.width - 48, 400)
        modal: true
        title: qsTr("Ce faci cu elementul?")

        ColumnLayout {
            width: parent.width
            spacing: 12

            Label {
                Layout.fillWidth: true
                text: actionDialog.word
                font.bold: true
                font.pixelSize: 18
                wrapMode: Text.Wrap
            }

            Button {
                Layout.fillWidth: true
                implicitHeight: 56
                text: qsTr("Modifică")
                onClicked: {
                    actionDialog.close()
                    editDialog.row = actionDialog.row
                    editField.text = actionDialog.word
                    editDialog.open()
                }
            }

            Button {
                Layout.fillWidth: true
                implicitHeight: 56
                text: qsTr("Șterge")
                onClicked: {
                    wordModel.remove(actionDialog.row)
                    actionDialog.close()
                }
            }
        }
    }

    // Fereastra de modificare: textul apare selectat și gata de scris
    Dialog {
        id: editDialog
        property int row: -1

        parent: Overlay.overlay
        anchors.centerIn: parent
        width: Math.min(parent.width - 48, 400)
        modal: true
        title: qsTr("Modifică")
        standardButtons: Dialog.Save | Dialog.Cancel

        TextField {
            id: editField
            width: parent.width
            onAccepted: editDialog.accept()
        }

        onOpened: {
            editField.forceActiveFocus()
            editField.selectAll()
        }
        onAccepted: wordModel.edit(row, editField.text)
    }

    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        model: wordModel

        // Mesaj când lista e goală
        Label {
            anchors.centerIn: parent
            visible: listView.count === 0
            text: qsTr("Nu ai niciun element încă")
            color: palette.mid
        }

        // Grupare pe litere
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
            implicitHeight: 56
            text: model.display

            onClicked: {
                actionDialog.row = index
                actionDialog.word = model.display
                actionDialog.open()
            }
        }
    }
}