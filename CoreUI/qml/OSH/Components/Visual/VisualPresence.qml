import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH.js 1.0

VisualActionButton {
    id: root

    property bool presenceActive: false

    SequentialAnimation on color {
        running: presenceActive

        ColorAnimation {
            to: "#440000FF"
            easing.type: Easing.InSine
            duration: 500
        }
        ColorAnimation {
            to: "white"
            duration: 500
            easing.type: Easing.OutSine
        }

        loops: Animation.Infinite
        alwaysRunToEnd: true
    }

    Image {
        anchors.fill: parent

        source: GFX.icon("baseline_person_black_24dp.png")
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.Pad

        /*
        layer.enabled: presenceActive
        layer.effect: ColorOverlay {
            color: "blue"
        }*/
    }

    MouseArea {
        anchors.fill: parent

        //onClicked: root.presenceActive = !root.presenceActive
    }
}
