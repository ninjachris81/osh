import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12

import OSH.js 1.0

Rectangle {
    id: root

    readonly property int buttonHeight: 50
    readonly property int buttonCount: 4
    property bool isOpen: false

    color: "white"

    height: 0

    opacity: 0

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

    Behavior on opacity {
        NumberAnimation {}
    }

    Behavior on height {
        NumberAnimation {
            duration: 100
        }
    }

    states: [
        State {
            when: root.isOpen
            name: "open"

            PropertyChanges {
                target: root
                height: buttonHeight * buttonCount
                opacity: 1
            }
        }
    ]

    Column {
        //spacing: 6
        anchors.fill: parent

        ButtonGroup  {
            id: buttonGroup

            onClicked: {
                VisualStateManager.currentFloor = button.floorIndex
            }
        }

        VisualFloorMenuButton {
            label: qsTr("Dach")
            floorIndex: 3
            checked: VisualStateManager.currentFloor === floorIndex
            ButtonGroup.group: buttonGroup
            height: root.buttonHeight
            anchors.left: parent.left
            anchors.right: parent.right
        }

        VisualFloorMenuButton  {
            text: qsTr("OG")
            floorIndex: 2
            checked: VisualStateManager.currentFloor === floorIndex
            ButtonGroup.group: buttonGroup
            height: root.buttonHeight
            anchors.left: parent.left
            anchors.right: parent.right
        }

        VisualFloorMenuButton  {
            text: qsTr("EG")
            floorIndex: 1
            checked: VisualStateManager.currentFloor === floorIndex
            ButtonGroup.group: buttonGroup
            height: root.buttonHeight
            anchors.left: parent.left
            anchors.right: parent.right
        }

        VisualFloorMenuButton  {
            text: qsTr("Keller")
            floorIndex: 0
            checked: VisualStateManager.currentFloor === floorIndex
            ButtonGroup.group: buttonGroup
            height: root.buttonHeight
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}
