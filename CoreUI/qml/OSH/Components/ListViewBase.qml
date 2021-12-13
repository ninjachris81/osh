import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ListView {
    id: root

    property int headerHeight: 30

    property var listHeaders: []
    property var listWidths: []
    property var listValues: []

    headerPositioning: ListView.OverlayHeader
    snapMode: ListView.SnapToItem

    header: Rectangle {
        height: root.headerHeight
        anchors.left: parent.left
        anchors.right: parent.right
        color: "gray"

        z: 10

        RowLayout {
            height: root.headerHeight

            Repeater {
                model: root.listHeaders.length

                Text {
                    Layout.margins: 2
                    Layout.preferredWidth: root.listWidths[index]
                    text: root.listHeaders[index]
                }
            }
        }
    }

    delegate: Item {
        height: root.headerHeight
        anchors.left: parent.left
        anchors.right: parent.right

        readonly property int rowIndex: index

        RowLayout {
            height: root.headerHeight

            Repeater {
                model: root.listHeaders.length

                Text {
                    Layout.margins: 2
                    Layout.preferredWidth: root.listWidths[index]
                    text: root.listValues[index](rowIndex)
                }
            }
        }
    }
}
