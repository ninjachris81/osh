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

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        knownRoomId: "mainFloor"

        width: 360
    }

    VisualRoom {
        id: floor

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 20
        anchors.left: mainFloor.right

        width: 800
        height: 170

        knownRoomId: "egFloor"
    }

    VisualRoom {
        id: kitchen

        anchors.left: floor.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.top: floor.top

        knownRoomId: "kitchen"
    }

    VisualRoom {
        id: vz

        anchors.right: kitchen.left
        anchors.bottom: parent.bottom
        anchors.top: floor.bottom

        width: 500

        knownRoomId: "supplyRoom"
    }

    VisualRoom {
        id: bath

        anchors.right: vz.left
        anchors.bottom: parent.bottom
        anchors.top: floor.bottom
        anchors.left: mainFloor.right

        gridColumns: 2

        knownRoomId: "toilet"
    }

    VisualRoom {
        id: ez

        anchors.right: parent.right
        anchors.bottom: kitchen.top
        anchors.top: parent.top

        width: 900

        knownRoomId: "diningRoom"
    }

    VisualRoom {
        id: az

        anchors.right: ez.left
        anchors.bottom: ez.bottom
        anchors.top: parent.top
        anchors.left: mainFloor.right

        knownRoomId: "workingRoom"
    }
}
