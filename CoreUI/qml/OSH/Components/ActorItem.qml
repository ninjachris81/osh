import QtQuick 2.12
import QtQuick.Layouts 1.12

ItemBase {
    id: root

    width: 200
    height: 150
    color: "red"
    radius: 4

    signal accepted()

    ColumnLayout {
        anchors.fill: parent

        Text {
            id: nameLabel
            Layout.alignment: Qt.AlignHCenter
            text: ref.fullId
        }

        Text {
            id: valueLabel
            font.bold: true
            font.pointSize: 16
            Layout.alignment: Qt.AlignHCenter
            text: ref.rawValue === undefined ? "Invalid" : ref.rawValue + " " + ref.unitTypeSuffix
        }

        TargetAnchor {
            id: inputAnchor
            name: "Start Play"
            Layout.alignment: Qt.AlignHCenter

            onAccepted: {
                root.accepted()
            }
        }
    }
}
