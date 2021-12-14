import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH 1.0
import OSH.js 1.0

VisualActionButton {
    id: root

    signal requestCmd(var cmd)

    property bool shutterClosed: false

    color: "white"

    Image {
        anchors.fill: parent

        source: GFX.icon("baseline_system_update_alt_black_24dp.png")
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.Pad

        /*
        layer.enabled: lightOn
        layer.effect: ColorOverlay {
            color: "yellow"
        }*/

        rotation: shutterClosed ? 180 : 0
    }

    MouseArea {
        anchors.fill: parent

        onClicked: root.requestCmd(shutterClosed ? ACTOR_CMDS.ACTOR_CMD_UP : ACTOR_CMDS.ACTOR_CMD_DOWN)
    }
}
