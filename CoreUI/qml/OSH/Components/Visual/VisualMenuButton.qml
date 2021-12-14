import QtQuick 2.0

import OSH.js 1.0

Rectangle {
    id: root

    signal trigger()

    width: 52
    height: 52

    color: "white"

    radius: 6

    Image {
        source: GFX.bigIcon("baseline_menu_black_48dp.png")
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.Pad
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.trigger()
    }

}
