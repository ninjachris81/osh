import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12

RadioButton {
    id: root

    //signal trigger()

    property alias label: labelText.text
    property int floorIndex: 0

    spacing: 10

    indicator: Item {
    }

    /*
    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: root.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        border.color: "black"

        Rectangle {
            width: 14
            height: 14
            x: 6
            y: 6
            radius: 7
            color: "black"
            visible: root.checked
        }
    }*/

    contentItem: Text {
        id: labelText
        text: root.text
        font.pointSize: 20
        opacity: enabled ? 1.0 : 0.3
        color: "black"
        font.bold: root.checked
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        leftPadding: root.indicator.width + root.spacing
    }
}
