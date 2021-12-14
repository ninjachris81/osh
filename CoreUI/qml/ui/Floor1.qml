import QtQuick 2.0

import OSH 1.0
import OSH.Components.Visual 1.0
import OSH.js 1.0


Item {
    id: root

    anchors.fill: parent
    anchors.margins: 5

    VisualRoom {
        id: mainFloor
        name: qsTr("HF")

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        hasShutter: false

        width: 360
    }

    VisualRoom {
        id: floor
        name: qsTr("Flur")

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 20
        anchors.left: mainFloor.right

        width: 800
        height: 170

        hasShutter: false
        hasBrightness: false
    }

    VisualRoom {
        id: kitchen
        name: qsTr("Küche")

        anchors.left: floor.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.top: floor.top


        readonly property int lightIndex: Commons.searchActorIndex("egRelays0.0")
        readonly property int brightnessIndex: Commons.searchValueIndex("brightnesses.0")
        readonly property int shutterIndex: Commons.searchActorIndex("egRelays0.1")
        readonly property int presenceActiveIndex: Commons.searchValueIndex("motions.0")
        readonly property int tempIndex: Commons.searchValueIndex("temps.0")

        onRequestLight: {
            console.info("Request Light " + cmd)
            DatamodelManager.datamodel.actors[lightIndex].triggerCmd(cmd)
        }

        onRequestShutter: {
            console.info("Request Light" + cmd)
            DatamodelManager.datamodel.actors[shutterIndex].triggerCmd(cmd)
        }

        Component.onCompleted: {
            lightIsValid = Qt.binding(function() { return DatamodelManager.datamodel.actors[lightIndex].isValid })
            lightOn = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.actors[lightIndex].rawValue, false) })

            brightnessIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[brightnessIndex].isValid })
            brightness = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[brightnessIndex].rawValue, 0) })

            shutterIsValid = Qt.binding(function() { return DatamodelManager.datamodel.actors[shutterIndex].isValid })
            shutterClosed = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.actors[shutterIndex].rawValue, false) })

            presenceIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[presenceActiveIndex].isValid })
            presenceActive = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[presenceActiveIndex].rawValue, false) })

            tempIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[tempIndex].isValid })
            temp = Qt.binding(function() { return Commons.formatValue(DatamodelManager.datamodel.values[tempIndex]) })
        }

    }

    VisualRoom {
        id: vz
        name: qsTr("VZ")

        anchors.right: kitchen.left
        anchors.bottom: parent.bottom
        anchors.top: floor.bottom

        width: 500
    }

    VisualRoom {
        id: bath
        name: qsTr("Bad")

        anchors.right: vz.left
        anchors.bottom: parent.bottom
        anchors.top: floor.bottom
        anchors.left: mainFloor.right

        hasShutter: false

        gridColumns: 2
    }

    VisualRoom {
        id: ez
        name: qsTr("EZ")

        anchors.right: parent.right
        anchors.bottom: kitchen.top
        anchors.top: parent.top

        width: 900
    }

    VisualRoom {
        id: az
        name: qsTr("AZ")

        anchors.right: ez.left
        anchors.bottom: ez.bottom
        anchors.top: parent.top
        anchors.left: mainFloor.right
    }
}
