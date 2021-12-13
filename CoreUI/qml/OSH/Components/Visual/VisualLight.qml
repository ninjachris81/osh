import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH.js 1.0

VisualActionButton {
    id: root

    property bool lightOn: false

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
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {

        }
    }
}
