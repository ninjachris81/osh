import QtQuick 2.0

import OSH 1.0
import OSH.Components.Visual 1.0
import OSH.js 1.0

Rectangle {
    anchors.fill: parent

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#ededed"; }
        GradientStop { position: 1.0; color: "#cccccc"; }
    }

    VisualHouse {
        anchors.fill: parent
        anchors.margins: 20

        Item {
            id: floorEG

            anchors.fill: parent
            anchors.margins: 5

            VisualRoom {
                id: mainFloor
                name: qsTr("HF")

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom

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

                Component.onCompleted: {
                    var lightIndex = Commons.searchValueIndex("egInputs0.0")
                    lightIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[lightIndex].isValid })
                    lightOn = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[lightIndex].rawValue, false) })

                    var brightnessIndex = Commons.searchValueIndex("brightnesses.0")
                    brightnessIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[brightnessIndex].isValid })
                    brightness = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[brightnessIndex].rawValue, 0) })

                    var shutterIndex = Commons.searchActorIndex("egRelays0.0")
                    shutterIsValid = Qt.binding(function() { return DatamodelManager.datamodel.actors[shutterIndex].isValid })
                    shutterClosed = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.actors[shutterIndex].rawValue, false) })

                    var presenceActiveIndex = Commons.searchValueIndex("motions.0")
                    presenceIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[presenceActiveIndex].isValid })
                    presenceActive = Qt.binding(function() { return Commons.value(DatamodelManager.datamodel.values[presenceActiveIndex].rawValue, false) })

                    var tempIndex = Commons.searchValueIndex("temps.0")
                    tempIsValid = Qt.binding(function() { return DatamodelManager.datamodel.values[tempIndex].isValid })
                    temp = Qt.binding(function() { return Commons.formatValue(DatamodelManager.datamodel.values[tempIndex]) })
                }
            }

            VisualRoom {
                id: kitchen
                name: qsTr("Küche")

                anchors.left: floor.right
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                anchors.top: floor.top
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
    }
}
