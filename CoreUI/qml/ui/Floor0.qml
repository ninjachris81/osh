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
        name: qsTr("HF")

        anchors.left: parent.left
        anchors.bottom: parent.bottom

        hasShutter: false
        hasTemp: false

        width: 360
        height: 700
    }

    VisualRoom {
        id: floor
        name: qsTr("Flur")

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -110
        anchors.left: mainFloor.right

        width: 600
        height: 150

        actionBar.anchors.verticalCenterOffset: 30

        hasShutter: false
        hasTemp: false
    }

    VisualRoom {
        id: l1
        name: qsTr("L1")

        anchors.right: mainFloor.right
        anchors.bottom: mainFloor.top
        anchors.top: parent.top
        anchors.left: parent.left

        hasShutter: false
        hasTemp: false
    }

    VisualRoom {
        id: l2
        name: qsTr("L2")

        anchors.left: l1.right
        anchors.right: floor.right
        anchors.bottom: floor.top
        anchors.top: parent.top

        hasShutter: false
        hasTemp: false
    }

    VisualRoom {
        id: l3
        name: qsTr("L3")

        anchors.left: wash.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: wash.top

        hasShutter: false
        hasTemp: false
    }

    VisualRoom {
        id: workshop
        name: qsTr("Werkstatt")

        anchors.left: floor.right
        anchors.right: parent.right
        anchors.bottom: l3.top
        anchors.top: parent.top

        hasShutter: false
        hasTemp: false
    }

    VisualRoom {
        id: wash
        name: qsTr("Heizraum")

        anchors.bottom: parent.bottom
        anchors.top: floor.bottom
        anchors.left: mainFloor.right

        width: 800

        hasShutter: false
        hasTemp: false

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

            VisualWater {
                id: waterFlowGarden
                iconSource: GFX.icon("baseline_yard_black_24dp.png")
            }
            VisualWater {
                id: waterFlowWarm
                iconColor: "#88FF0000"
                activeColor: "#44FF0000"
            }
            VisualWater {
                id: waterFlowCold
            }
            VisualWater {
                id: waterFlowToilet
                iconSource: GFX.icon("18_toilet-512_6285.png")
            }

            Component.onCompleted: {
                waterFlowGarden.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowGardenIndex].isValid })
                waterFlowGarden.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowGardenIndex].rawValue, 0) })

                waterFlowWarm.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowWarmIndex].isValid })
                waterFlowWarm.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowWarmIndex].rawValue, 0) })

                waterFlowCold.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowColdIndex].isValid })
                waterFlowCold.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowColdIndex].rawValue, 0) })

                waterFlowToilet.isValid = Qt.binding(function() { return DatamodelManager.datamodel.values[waterFlowToiletIndex].isValid })
                waterFlowToilet.waterFlow = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[waterFlowToiletIndex].rawValue, 0) })
            }
        }
    }
}
