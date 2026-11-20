import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    // Fereastra de modificare, deschisă la apăsarea pe un cuvânt
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
            text: qsTr("Nu ai niciun cuvânt încă")
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
            text: model.display

            onClicked: {
                editDialog.row = index
                editField.text = model.display
                editDialog.open()
                editField.forceActiveFocus()
                editField.selectAll()
            }

            ToolButton {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: "✕"
                onClicked: wordModel.remove(index)
            }
        }
    }
}