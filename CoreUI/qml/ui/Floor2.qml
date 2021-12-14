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
        anchors.bottom: parent.bottom

        hasShutter: false

        width: 360
        height: 700
    }

    VisualRoom {
        id: floor
        name: qsTr("Flur")

        readonly property int lightIndex: Commons.searchActorIndex("egRelays0.0")
        readonly property int brightnessIndex: Commons.searchValueIndex("brightnesses.0")
        readonly property int presenceActiveIndex: Commons.searchValueIndex("motions.0")
        readonly property int tempIndex: Commons.searchValueIndex("temps.0")

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 20
        anchors.left: mainFloor.right

        width: 800
        height: 170

        onRequestLight: {
            console.info("Request Light " + cmd)
            DatamodelManager.datamodel.actors[lightIndex].triggerCmd(cmd)
        }

        Component.onCompleted: {
            lightIsValid = Qt.binding(function() { return DatamodelManager.datamodel.actors[lightIndex].isValid })
            lightOn = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.actors[lightIndex].rawValue, false) })

            brightnessIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[brightnessIndex].isValid })
            brightness = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[brightnessIndex].rawValue, 0) })

            presenceIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[presenceActiveIndex].isValid })
            presenceActive = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[presenceActiveIndex].rawValue, false) })

            tempIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[tempIndex].isValid })
            temp = Qt.binding(function() { return Commons.formatValue(DatamodelManager.datamodel.values[tempIndex]) })
        }

        hasShutter: false
    }

    VisualRoom {
        id: az
        name: qsTr("AZ")

        anchors.left: floor.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.top: floor.top
    }

    VisualRoom {
        id: wz
        name: qsTr("WZ")

        anchors.right: sz.left
        anchors.bottom: sz.bottom
        anchors.top: parent.top
        anchors.left: mainFloor.right
    }

    VisualRoom {
        id: sz
        name: qsTr("SZ")

        anchors.right: parent.right
        anchors.bottom: az.top
        anchors.top: parent.top

        width: 900
    }

    VisualRoom {
        id: bath
        name: qsTr("Bad")

        anchors.right: az.left
        anchors.bottom: az.bottom
        anchors.top: floor.bottom
        anchors.left: mainFloor.right
    }
}
