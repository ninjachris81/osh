import QtQuick 2.12
import QtQuick.Layouts 1.12

ItemBase {
    id: root

    property int anchorOffsetX: valueAnchor.x + (valueAnchor.width / 2)
    property int anchorOffsetY: valueAnchor.y + (valueAnchor.height / 2)

    signal startDrag()

    width: 200
    height: 150
    color: "lightblue"
    radius: 4

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

        SourceAnchor {
            id: valueAnchor
            name: "Value"
            Layout.alignment: Qt.AlignHCenter

            onStartDrag: {
                root.startDrag()
            }
        }
    }
}
