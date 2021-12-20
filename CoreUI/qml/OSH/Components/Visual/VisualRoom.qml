import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH.Components.Visual 1.0

Item {
    id: root

    property string name: ""

    //DebugTracer {}

    property alias gridColumns: actionBar.gridColumns
    property alias actionBar: actionBar

    signal requestLight(var cmd)
    property alias hasLight: actionBar.hasShutter
    property alias lightIsValid: actionBar.lightIsValid
    property alias lightOn: actionBar.lightOn

    signal requestShutter(var cmd)
    property alias hasShutter: actionBar.hasShutter
    property alias shutterIsValid: actionBar.shutterIsValid
    property alias shutterClosed: actionBar.shutterClosed

    property alias hasBrightness: actionBar.hasBrightness
    property alias brightnessIsValid: actionBar.brightnessIsValid
    property alias brightness: actionBar.brightness

    property alias hasPresence: actionBar.hasPresence
    property alias presenceIsValid: actionBar.presenceIsValid
    property alias presenceActive: actionBar.presenceActive

    property alias hasTemp: actionBar.hasTemp
    property alias tempIsValid: actionBar.tempIsValid
    property alias temp: actionBar.temp

    property alias hasHumidity: actionBar.hasHumidity
    property alias humidityIsValid: actionBar.humidityIsValid
    property alias humidity: actionBar.humidity

    property color roomColor: Qt.rgba(1, 1, 1, hasBrightness ? (brightness / 100) : 0.5)

    opacity: 0.8

    states: [
        State {
            name: "lightOn"

            when: lightOn

            PropertyChanges {
                target: root
                roomColor: "yellow"
                opacity: 1
            }
        }
    ]


    Behavior on opacity {
        NumberAnimation {}
    }

    Behavior on brightness {
        NumberAnimation {
            duration: 3000
        }
    }

    Rectangle {
        id: roomOutline
        anchors.fill: parent

        radius: 6

        border.color: "white"
        border.width: 2

        //opacity: 0.2
        color: roomColor

        anchors.margins: 5

        Text {
            id: roomLabel
            anchors.fill: parent
            anchors.bottomMargin: 50
            text: root.name
            opacity: 0.4
            font.pointSize: 20
            color: "black"

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        VisualActionBar {
            id: actionBar
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 40

            onRequestLight: root.requestLight(cmd)
            onRequestShutter: root.requestShutter(cmd)
        }

        layer.enabled: true
        layer.effect: DropShadow {
            //anchors.fill: parent
            radius: 8
            samples: 17
            color: "black"
            transparentBorder: true
            horizontalOffset: 2
            verticalOffset: 2
            spread: 0
            //source: parent
        }
    }
}
