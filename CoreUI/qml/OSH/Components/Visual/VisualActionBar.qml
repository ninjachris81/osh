import QtQuick 2.0
import QtQuick.Layouts 1.12

import OSH.Components.Visual 1.0
import "."

Rectangle {
    id: root

    signal requestLight(var cmd)
    property bool hasLight: true
    property alias lightIsValid: light.isValid
    property alias lightOn: light.lightOn

    property bool hasBrightness: true
    property alias brightnessIsValid: light.brightnessIsValid
    property alias brightness: light.brightness

    signal requestShutter(var cmd)
    property bool hasShutter: true
    property alias shutterIsValid: shutter.isValid
    property alias shutterClosed: shutter.shutterClosed

    property bool hasPresence: true
    property alias presenceIsValid: presence.isValid
    property alias presenceActive: presence.presenceActive

    property bool hasTemp: true
    property alias tempIsValid: temp.isValid
    property alias temp: temp.temp

    property alias gridColumns: gridLayout.columns
    readonly property int buttonWidth: 50

    //border.color: "white"
    //border.width: 2

    readonly property int buttonCount: (hasLight ? 1 : 0) + (hasShutter ? 1 : 0) + (hasPresence ? 1 : 0) + (hasTemp ? 1 : 0)

    width: Math.min(gridColumns, buttonCount) * buttonWidth
    height: 50

    color: "transparent"

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        columns: 4

        VisualLight {
            id: light
            visible: root.hasLight
            Layout.alignment: Qt.AlignCenter
            onRequestCmd: root.requestLight(cmd)
        }

        VisualShutter {
            id: shutter
            visible: root.hasShutter
            Layout.alignment: Qt.AlignCenter
            onRequestCmd: root.requestShutter(cmd)
        }

        VisualPresence {
            id: presence
            visible: root.hasPresence
            Layout.alignment: Qt.AlignCenter
        }

        VisualTemp {
            id: temp
            visible: root.hasTemp
            Layout.alignment: Qt.AlignCenter
        }
    }

}
