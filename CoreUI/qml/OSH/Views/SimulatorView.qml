import QtQuick 2.12
import QtQuick.Controls 2.12

import OSH 1.0
import OSH.Components 1.0
import OSH.Components.Simulator 1.0

ViewBase {
    id: root

    property var activeConnector

    function clearConnector() {
        if (root.activeConnector) {
            root.activeConnector.destroy()
        }
    }

    function createConnector(source) {
        clearConnector()
        root.activeConnector = connectorComp.createObject(source, {from: source, globalMouseArea: mouseArea});
    }

    Component {
        id: connectorComp
        ConnectorBase {
        }
    }

    SimulatorActionBar {
        id: actionBar
        anchors.left: parent.left
        anchors.right: parent.right
    }


    Flickable {
        id: flickable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: actionBar.bottom
        anchors.bottom: parent.bottom

        contentWidth: 6000
        contentHeight: 6000

        clip: true

        boundsMovement: Flickable.StopAtBounds
        boundsBehavior: Flickable.StopAtBounds

        ScrollIndicator.vertical: ScrollIndicator { }
        ScrollIndicator.horizontal: ScrollIndicator { }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                clearConnector()
            }

            Repeater {
                model: DatamodelManager.datamodel.values

                ValueItem {
                    ref: modelData  //DatamodelManager.datamodel.values[index]
                    onStartDrag: createConnector(this)
                }
            }

            Repeater {
                model: DatamodelManager.datamodel.actors


                ActorItem {
                    ref: modelData //DatamodelManager.datamodel.actors[0]

                    onAccepted: {
                        console.log("Accepted")
                        clearConnector()
                    }
                }

            }
        }
    }
}
