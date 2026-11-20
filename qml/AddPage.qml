import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    function addCurrentText() {
        if (wordModel.add(input.text))
            input.clear()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Label {
            text: qsTr("Cuvânt nou")
            font.pixelSize: 22
            font.bold: true
        }

        TextField {
            id: input
            Layout.fillWidth: true
            placeholderText: qsTr("Scrie un cuvânt sau o frază")
            onAccepted: addCurrentText()
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Adaugă")
            onClicked: addCurrentText()
        }

        Item { Layout.fillHeight: true } // împinge conținutul în sus
    }
}