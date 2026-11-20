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
        // lasă loc sub bara de stare (ceas, baterie) din partea de sus
        anchors.topMargin: SafeArea.margins.top
        currentIndex: tabBar.currentIndex

        AddPage {}
        ListPage {}
    }

    footer: TabBar {
        id: tabBar
        // ridică taburile deasupra barei de sistem, dacă aceasta e vizibilă
        bottomPadding: SafeArea.margins.bottom

        TabButton {
            text: qsTr("Adaugă")
            implicitHeight: 64
            font.pixelSize: 18
        }
        TabButton {
            text: qsTr("Lista")
            implicitHeight: 64
            font.pixelSize: 18
        }
    }
}