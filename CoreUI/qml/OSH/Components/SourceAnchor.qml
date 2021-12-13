import QtQuick 2.0

import OSH 1.0

Item {
    id: root

    property alias name : name.text
    signal startDrag()

    width: 30
    height: 30

    Column {
        Text {
            id: name
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: anchorPoint
            radius: 10
            width: 20
            height: 20
            color: "blue"

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    root.startDrag()
                }
            }
        }
    }

}
