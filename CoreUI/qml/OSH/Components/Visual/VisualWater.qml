import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH 1.0
import OSH.js 1.0

VisualActionButton {
    id: root

    property double waterFlow
    property bool waterFlowActive: isValid && waterFlow > 0.0

    property double waterLevel

    property color iconColor: "#880000FF"
    property color activeColor: "#440000FF"
    property alias iconSource: icon.source

    SequentialAnimation on color {
        running: waterFlowActive

        ColorAnimation {
            to: activeColor
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
        id: icon
        anchors.fill: parent

        source: GFX.icon("baseline_water_drop_black_24dp.png")
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.Pad

        layer.enabled: iconColor
        layer.effect: ColorOverlay {
            color: iconColor
        }

        anchors.bottomMargin: isValid ? 6 : 0
    }

    Text {
        id: waterValue
        text: waterFlowActive ? Commons.addTypeSuffix(root.waterFlow, UNIT_TYPE.UT_LITER_PER_MIN, isValid) : Commons.addTypeSuffix(root.waterLevel, UNIT_TYPE.UT_LITERS, isValid)
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: !isValid ? 0 : 3
        anchors.bottomMargin: 3
    }

    MouseArea {
        anchors.fill: parent
    }
}
