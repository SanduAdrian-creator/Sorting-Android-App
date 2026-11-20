import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 360
    height: 640
    title: qsTr("Cuvinte")

    StackLayout {
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        AddPage {}
        ListPage {}
    }

    // Taburile de jos
    footer: TabBar {
        id: tabBar

        TabButton { text: qsTr("Adaugă") }
        TabButton { text: qsTr("Lista") }
    }
}