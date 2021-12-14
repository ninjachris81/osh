import QtQuick 2.0

Item {
    id: root

    height: 50
    width: 160

    Text {
        id: timeLabel
        anchors.fill: parent
        text: Qt.formatTime(new Date(),"hh:mm")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pointSize: 20
    }

    Timer {
        interval: 10000
        repeat: true
        running: true
        onTriggered: timeLabel.text =  Qt.formatTime(new Date(),"hh:mm")
    }
}
