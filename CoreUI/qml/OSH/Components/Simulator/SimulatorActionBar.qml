import QtQuick 2.0
import QtQuick.Layouts 1.3

import OSH 1.0

import OSH.js 1.0

Rectangle {
    id: root

    height: 54

    color: "grey"

    RowLayout {
        id: buttonBar

        anchors.fill: parent
        spacing: 2

        SimulatorButton {
            iconSource: GFX.bigIcon("baseline_save_black_48dp.png")

            onTrigger: DatamodelManager.save()
        }

        Item {
            Layout.fillWidth: true
        }
    }

    Rectangle {
        anchors.top: buttonBar.bottom
        anchors.left: buttonBar.left
        anchors.right: buttonBar.right

        height: 1
        color: "black"
    }

}
