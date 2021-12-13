import QtQuick 2.0
import OSH 1.0

ConnectorItem {
    id: root

    property var globalMouseArea

    property var from
    property int fromOffsetX: from.anchorOffsetX
    property int fromOffsetY: from.anchorOffsetY

    anchors.left: from.left
    anchors.top: from.top

    anchors.leftMargin: fromOffsetX
    anchors.topMargin: fromOffsetY

    property var to

    color: "black"

    width: (to ? 0 : globalMouseArea.mouseX - root.x)
    height: (to ? 0 : globalMouseArea.mouseY - root.y)
}
