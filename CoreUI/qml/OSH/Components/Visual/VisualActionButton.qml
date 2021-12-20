import QtQuick 2.0

Rectangle {
    id: root

    width: 50
    height: 50

    property bool isValid
    property bool markAsInvalid: !isValid

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

        PauseAnimation {
            duration: 500
        }

        ColorAnimation {
            to: "black"
            duration: 250
            easing.type: Easing.OutSine
        }

        PauseAnimation {
            duration: 500
        }

        loops: Animation.Infinite
    }

}

