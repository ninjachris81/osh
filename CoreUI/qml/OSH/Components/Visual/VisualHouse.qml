import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    radius: 6

    border.color: "white"
    border.width: 2

    color: "gray"
    opacity: 0.5

    layer.enabled: true
    layer.effect: DropShadow {
        //anchors.fill: parent
        radius: 8
        samples: 17
        color: "black"
        transparentBorder: true
        horizontalOffset: 2
        verticalOffset: 2
        spread: 0
        //source: parent
    }
}
