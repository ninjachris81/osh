import QtQuick 2.0
import QtQuick.Layouts 1.12

import OSH.Components.Visual 1.0
import "."

Rectangle {
    id: root

    property alias lightIsValid: light.isValid
    property alias lightOn: light.lightOn

    property alias brightnessIsValid: shutter.brightnessIsValid
    property alias brightness: shutter.brightness

    property alias shutterIsValid: shutter.isValid
    property alias shutterClosed: shutter.shutterClosed

    property alias presenceIsValid: presence.isValid
    property alias presenceActive: presence.presenceActive

    property alias tempIsValid: temp.isValid
    property alias temp: temp.temp

    property alias gridColumns: gridLayout.columns

    //border.color: "white"
    //border.width: 2

    readonly property int maxColumns: 4

    width: gridColumns === 2 ? 2 * 50 : maxColumns * 50
    height: 50

    color: "transparent"

    GridLayout {
        id: gridLayout
        anchors.fill: parent

        VisualLight {
            id: light
            Layout.alignment: Qt.AlignCenter
        }

        VisualShutter {
            id: shutter
            Layout.alignment: Qt.AlignCenter
        }

        VisualPresence {
            id: presence
            Layout.alignment: Qt.AlignCenter
        }

        VisualTemp {
            id: temp
            Layout.alignment: Qt.AlignCenter
        }

    }

}
