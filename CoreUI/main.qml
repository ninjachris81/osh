import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("OSH Editor")

    TabBar {
        id: bar

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 40

        TabButton {
            text: qsTr("Dashboard")
        }
        TabButton {
            text: qsTr("Device Explorer")
        }
        TabButton {
            text: qsTr("Task View")
        }
        TabButton {
            text: qsTr("Value View")
        }
        TabButton {
            text: qsTr("Actor View")
        }
    }

    StackLayout {
        anchors.fill: parent
        anchors.topMargin: bar.height
        clip: true

        currentIndex: bar.currentIndex

        DashboardView {

        }

        DeviceDiscoveryView {

        }

        TaskView {

        }

        ValueView {

        }

        ActorView {

        }
    }


}
