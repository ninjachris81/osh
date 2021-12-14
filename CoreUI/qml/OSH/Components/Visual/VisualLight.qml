import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH 1.0
import OSH.js 1.0

VisualActionButton {
    id: root

    signal requestCmd(var cmd)
    property bool lightOn: false

    property bool brightnessIsValid
    property int brightness

    color: lightOn ? "black" : "white"

    Image {
        anchors.fill: parent

        source: GFX.icon("baseline_lightbulb_black_24dp.png")
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.Pad

        layer.enabled: lightOn
        layer.effect: ColorOverlay {
            color: "yellow"
        }

        anchors.bottomMargin: brightnessIsValid ? 6 : 0
    }

    Text {
        id: brightnessValue
        text: Commons.addTypeSuffix(root.brightness, UNIT_TYPE.UT_PERCENT, brightnessIsValid)
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: brightnessIsValid ? 0 : 2
        anchors.bottomMargin: 3
    }

    MouseArea {
        anchors.fill: parent

        onClicked: root.requestCmd(lightOn ? ACTOR_CMDS.ACTOR_CMD_OFF : ACTOR_CMDS.ACTOR_CMD_ON)
    }
}
