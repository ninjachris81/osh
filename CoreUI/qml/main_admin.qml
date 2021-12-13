import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH.Views 1.0

Item {
    anchors.fill: parent

    TabBar {
        id: bar

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 40

        /*
        TabButton {
            text: qsTr("Dashboard")
        }
        */


        TabButton {
            text: qsTr("Visual Editor")
        }
        TabButton {
            text: qsTr("Device Explorer")
        }
        TabButton {
            text: qsTr("Tasks")
        }
        TabButton {
            text: qsTr("Values")
        }
        TabButton {
            text: qsTr("Actors")
        }
        TabButton {
            text: qsTr("Live Log")
        }
    }

    StackLayout {
        anchors.fill: parent
        anchors.topMargin: bar.height
        clip: true

        currentIndex: bar.currentIndex

        /*
        DashboardView {

        }
        */

        VisualEditorView {

        }

        DeviceDiscoveryView {

        }

        TaskView {

        }

        ValueView {

        }

        ActorView {

        }

        LiveLogView {

        }
    }


}
