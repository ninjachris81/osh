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
        knownRoomId: "mainFloor"

        width: 360
        height: 700
    }

    VisualRoom {
        id: floor
        knownRoomId: "ogFloor"

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 20
        anchors.left: mainFloor.right

        width: 800
        height: 170
    }

    VisualRoom {
        id: az
        knownRoomId: "clothingRoom"

        anchors.left: floor.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.top: floor.top
    }

    VisualRoom {
        id: wz
        knownRoomId: "livingRoom"

        anchors.right: sz.left
        anchors.bottom: sz.bottom
        anchors.top: parent.top
        anchors.left: mainFloor.right
    }

    VisualRoom {
        id: sz
        knownRoomId: "sleepingRoom"

        anchors.right: parent.right
        anchors.bottom: az.top
        anchors.top: parent.top

        width: 900
    }

    VisualRoom {
        id: bath
        knownRoomId: "bathRoom"

        anchors.right: az.left
        anchors.bottom: az.bottom
        anchors.top: floor.bottom
        anchors.left: mainFloor.right
    }
}
