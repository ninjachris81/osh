import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("OSH Editor")

    Loader {
        anchors.fill: parent

        source: "ui/main_ui.qml"
        //source: "main_admin.qml"
    }

}

