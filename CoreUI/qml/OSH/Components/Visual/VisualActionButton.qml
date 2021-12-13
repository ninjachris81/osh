import QtQuick 2.0

Rectangle {
    id: root

    width: 50
    height: 50

    property bool isValid

    radius: 6

    border.color: "black"
    border.width: isValid ? 2 : 3

    SequentialAnimation on border.color {
        running: !isValid

        alwaysRunToEnd: true

        ColorAnimation {
            to: "red"
            easing.type: Easing.InSine
            duration: 250
        }
        ColorAnimation {
            to: "black"
            duration: 250
            easing.type: Easing.OutSine
        }

        loops: Animation.Infinite
    }

}

