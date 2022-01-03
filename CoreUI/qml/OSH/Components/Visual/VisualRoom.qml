import QtQuick 2.0
import QtGraphicalEffects 1.0

import OSH 1.0
import OSH.Components.Visual 1.0
import OSH.js 1.0

Item {
    id: root

    property string knownRoomId
    property string name: _internal.knownRoom.name

    //DebugTracer {}

    property alias gridColumns: actionBar.gridColumns
    property alias actionBar: actionBar

    property int lightIndex
    signal requestLight(var cmd)
    property alias hasLight: actionBar.hasLight
    property alias lightIsValid: actionBar.lightIsValid
    property alias lightOn: actionBar.lightOn

    property int shutterIndex
    signal requestShutter(var cmd)
    property alias hasShutter: actionBar.hasShutter
    property alias shutterIsValid: actionBar.shutterIsValid
    property alias shutterClosed: actionBar.shutterClosed

    property int brightnessIndex
    property alias hasBrightness: actionBar.hasBrightness
    property alias brightnessIsValid: actionBar.brightnessIsValid
    property alias brightness: actionBar.brightness

    property int motionIndex
    property alias hasPresence: actionBar.hasPresence
    property alias presenceIsValid: actionBar.presenceIsValid
    property alias presenceActive: actionBar.presenceActive

    property int tempIndex
    property alias hasTemp: actionBar.hasTemp
    property alias tempIsValid: actionBar.tempIsValid
    property alias temp: actionBar.temp

    property int humidityIndex
    property alias hasHumidity: actionBar.hasHumidity
    property alias humidityIsValid: actionBar.humidityIsValid
    property alias humidity: actionBar.humidity

    property color roomColor: Qt.rgba(1, 1, 1, hasBrightness ? (brightness / 100) : 0.5)

    QtObject {
        id: _internal

        property var knownRoom
    }

    onRequestLight: {
        console.info("Request Light " + cmd)

        /*
        var inputIndex = Commons.searchIndexByValueType(VALUE_TYPE.VT_SWITCH, _internal.knownRoom.values, DatamodelManager.datamodel.values);
        if (inputIndex !== -1) {
            var value = DatamodelManager.datamodel.values[inputIndex]
            value.updateValue(true)
            ValueManager.publishValue(value)
            value.updateValue(false)
            ValueManager.publishValue(value)
        } else {
            console.warn("No input switch found")
        }*/
    }

    onRequestShutter: {
        console.info("Request Light" + cmd)
        DatamodelManager.datamodel.actors[shutterIndex].triggerCmd(cmd, "Clicked UI")
    }

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

    Component.onCompleted: {
        if (root.knownRoomId) {
            _internal.knownRoom = Commons.selectRoom(root.knownRoomId)

            if (_internal.knownRoom) {
                lightIndex = Commons.searchIndexByValueType(VALUE_TYPE.VT_RELAY_LIGHT, _internal.knownRoom.actors, DatamodelManager.datamodel.actors);
                hasLight = lightIndex != -1
                if (hasLight) {
                    console.info("Binding light for room " + root.knownRoomId)
                    lightIsValid = Qt.binding(function() { return DatamodelManager.datamodel.actors[lightIndex].isValid })
                    lightOn = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.actors[lightIndex].rawValue, false) })
                } else {
                    hasLight = false
                }

                brightnessIndex = Commons.searchIndexByValueType(VALUE_TYPE.VT_BRIGHTNESS, _internal.knownRoom.values, DatamodelManager.datamodel.values);
                hasBrightness = brightnessIndex != -1
                if (hasBrightness) {
                    console.info("Binding brightness for room " + root.knownRoomId)
                    brightnessIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[brightnessIndex].isValid })
                    brightness = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[brightnessIndex].rawValue, 0) })
                }

                shutterIndex = Commons.searchIndexByValueType(VALUE_TYPE.VT_RELAY_SHUTTER, _internal.knownRoom.actors, DatamodelManager.datamodel.actors);
                hasShutter = shutterIndex != -1
                if (hasShutter) {
                    console.info("Binding shutter for room " + root.knownRoomId)
                    shutterIsValid = Qt.binding(function() { return DatamodelManager.datamodel.actors[shutterIndex].isValid })
                    shutterClosed = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.actors[shutterIndex].rawValue, false) })
                }

                motionIndex = Commons.searchIndexByValueType(VALUE_TYPE.VT_MOTION, _internal.knownRoom.values, DatamodelManager.datamodel.values);
                hasPresence = motionIndex != -1
                if (hasPresence) {
                    console.info("Binding motion for room " + root.knownRoomId)
                    presenceIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[motionIndex].isValid })
                    presenceActive = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[motionIndex].rawValue, false) })
                }

                tempIndex = Commons.searchIndexByValueType(VALUE_TYPE.VT_TEMP, _internal.knownRoom.values, DatamodelManager.datamodel.values);
                hasTemp = tempIndex != -1
                if (hasTemp) {
                    console.info("Binding temp for room " + root.knownRoomId)
                    tempIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[tempIndex].isValid })
                    temp = Qt.binding(function() { return Commons.formatDoubleValue(DatamodelManager.datamodel.values[tempIndex]) })
                }

                humidityIndex = Commons.searchIndexByValueType(VALUE_TYPE.VT_HUMIDITY, _internal.knownRoom.values, DatamodelManager.datamodel.values);
                hasHumidity = humidityIndex != -1
                if (hasHumidity) {
                    console.info("Binding humidity for room " + root.knownRoomId)
                    humidityIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[humidityIndex].isValid })
                    humidity = Qt.binding(function() { return Commons.formatDoubleValue(DatamodelManager.datamodel.values[humidityIndex]) })
                }
            }
        }
    }
}
