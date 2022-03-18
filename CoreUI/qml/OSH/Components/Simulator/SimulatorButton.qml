import QtQuick 2.0

Rectangle {
    id: root

    property alias iconSource: icon.source

    signal trigger()

    width: 50
    height: 50

    color: "white"

    radius: 6

    MouseArea {
        anchors.fill: parent
        onClicked: root.trigger()
    }


    Image {
        id: icon
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.Pad
    }

}
