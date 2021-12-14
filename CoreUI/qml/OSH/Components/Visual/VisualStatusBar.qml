import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    signal triggerFloorMenu()

    property alias floorLabelLeft: floorLabel.x
    property alias floorLabelWidth: floorLabel.width

    height: menuButton.height
    width: menuButton.width + floorLabel.width + clock.width

    color: "white"
    radius: 6

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


    Row {
        VisualMenuButton {
            id: menuButton

            //onTrigger: root.triggerMenu()
        }

        Text {
            id: floorLabel
            text: VisualStateManager.currentFloorName
            font.pointSize: 20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 200

            MouseArea {
                anchors.fill: parent
                onClicked: root.triggerFloorMenu()
            }
        }

        VisualClock {
            id: clock
        }
    }
}
