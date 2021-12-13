import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH 1.0
import OSH.js 1.0

VisualActionButton {
    id: root

    property bool brightnessIsValid
    property int brightness

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
        anchors.bottomMargin: 6
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

        onClicked: root.shutterClosed = !root.shutterClosed
    }
}
