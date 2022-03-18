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
        root.visible = ref.visible
    }

    onXChanged: {
        ref.x = root.x
    }

    onYChanged: {
        ref.y = root.y
    }

}
