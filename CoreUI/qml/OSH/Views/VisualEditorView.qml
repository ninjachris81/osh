import QtQuick 2.12
import QtQuick.Controls 2.12

import OSH 1.0
import OSH.Components 1.0

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

    Flickable {
        id: flickable
        anchors.fill: parent

        contentWidth: 6000
        contentHeight: 6000

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


            ValueItem {
                id: val0
                ref: DatamodelManager.datamodel.values[0]
                onStartDrag: createConnector(this)
            }

            ValueItem {
                id: val1
                x: 100

                ref: DatamodelManager.datamodel.values[1]
                onStartDrag: createConnector(this)
            }

            ActorItem {
                id: act0
                x: 30
                y: 100
                ref: DatamodelManager.datamodel.actors[0]

                onAccepted: {
                    console.log("Accepted")
                    clearConnector()
                }
            }
        }
    }
}
