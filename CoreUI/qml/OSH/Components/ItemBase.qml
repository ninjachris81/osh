import QtQuick 2.12

Rectangle {
    id: root

    property var ref

    Drag.active: mouseArea.drag.active

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: parent
    }


    onRefChanged: {
        root.x = ref.x
        root.y = ref.y
    }
}
