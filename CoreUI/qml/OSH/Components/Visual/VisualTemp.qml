import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH.js 1.0

VisualActionButton {
    id: root

    property string temp

    Image {
        anchors.fill: parent

        source: GFX.icon("baseline_thermostat_black_24dp.png")
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.Pad

        /*
        layer.enabled: presenceActive
        layer.effect: ColorOverlay {
            color: "blue"
        }*/

        anchors.bottomMargin: temp ? 6 : 0
    }

    Text {
        id: tempValue
        text: root.temp
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: !isValid ? 0 : 3
        anchors.bottomMargin: 3
    }

    MouseArea {
        anchors.fill: parent
    }
}
