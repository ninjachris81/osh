import QtQuick 2.0
import QtQuick.Layouts 1.12

import OSH 1.0
import OSH.Components.Visual 1.0
import OSH.js 1.0


Item {
    id: root

    anchors.fill: parent
    anchors.margins: 5

    VisualRoom {
        id: mainFloor
        knownRoomId: "basementFloor0"

        anchors.left: parent.left
        anchors.bottom: parent.bottom

        width: 360
        height: 700
    }

    VisualRoom {
        id: floor
        knownRoomId: "basementFloor1"

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -110
        anchors.left: mainFloor.right

        width: 600
        height: 150

        actionBar.anchors.verticalCenterOffset: 30
    }

    VisualRoom {
        id: l1
        knownRoomId: "storage1"

        anchors.right: mainFloor.right
        anchors.bottom: mainFloor.top
        anchors.top: parent.top
        anchors.left: parent.left
    }

    VisualRoom {
        id: l2
        knownRoomId: "storage2"

        anchors.left: l1.right
        anchors.right: floor.right
        anchors.bottom: floor.top
        anchors.top: parent.top
    }

    VisualRoom {
        id: l3
        knownRoomId: "storage3"

        anchors.left: wash.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: wash.top
    }

    VisualRoom {
        id: workshop
        knownRoomId: "workshop"

        anchors.left: floor.right
        anchors.right: parent.right
        anchors.bottom: l3.top
        anchors.top: parent.top
    }

    VisualRoom {
        id: wash

        anchors.bottom: parent.bottom
        anchors.top: floor.bottom
        anchors.left: mainFloor.right

        width: 800

        knownRoomId: "heatingRoom"

        ColumnLayout {
            id: waterGridLayout

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 100

            readonly property int waterFlowGardenIndex: Commons.searchValueIndex("waterFlows.garden")
            readonly property int waterFlowWarmIndex: Commons.searchValueIndex("waterFlows.warm")
            readonly property int waterFlowColdIndex: Commons.searchValueIndex("waterFlows.cold")
            readonly property int waterFlowToiletIndex: Commons.searchValueIndex("waterFlows.toilet")

            readonly property int waterLevelGardenIndex: Commons.searchValueIndex("waterLevels.garden")
            readonly property int waterLevelWarmIndex: Commons.searchValueIndex("waterLevels.warm")
            readonly property int waterLevelColdIndex: Commons.searchValueIndex("waterLevels.cold")
            readonly property int waterLevelToiletIndex: Commons.searchValueIndex("waterLevels.toilet")

            VisualWater {
                id: waterGarden
                iconSource: GFX.icon("baseline_yard_black_24dp.png")
            }
            VisualWater {
                id: waterWarm
                iconColor: "#88FF0000"
                activeColor: "#44FF0000"
            }
            VisualWater {
                id: waterCold
            }
            VisualWater {
                id: waterToilet
                iconSource: GFX.icon("18_toilet-512_6285.png")
            }

            Component.onCompleted: {
                waterGarden.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowGardenIndex].isValid && DatamodelManager.datamodel.values[waterLevelGardenIndex].isValid })
                waterGarden.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowGardenIndex].rawValue, 0) })
                waterGarden.waterLevel = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterLevelGardenIndex].rawValue, 0) })

                waterWarm.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowWarmIndex].isValid && DatamodelManager.datamodel.values[waterLevelWarmIndex].isValid })
                waterWarm.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowWarmIndex].rawValue, 0) })
                waterWarm.waterLevel = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterLevelWarmIndex].rawValue, 0) })

                waterCold.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowColdIndex].isValid && DatamodelManager.datamodel.values[waterLevelColdIndex].isValid })
                waterCold.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowColdIndex].rawValue, 0) })
                waterCold.waterLevel = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterLevelColdIndex].rawValue, 0) })

                waterToilet.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowToiletIndex].isValid && DatamodelManager.datamodel.values[waterLevelToiletIndex].isValid })
                waterToilet.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowToiletIndex].rawValue, 0) })
                waterToilet.waterLevel = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterLevelToiletIndex].rawValue, 0) })
            }
        }
    }
}
