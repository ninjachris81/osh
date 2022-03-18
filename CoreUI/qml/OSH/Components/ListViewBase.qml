import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ListView {
    id: root

    property bool selectable: false

    property int headerHeight: 30

    property var listHeaders: []
    property var listWidths: []
    property var listValues: []

    signal itemClicked(var mouse, int index)

    headerPositioning: ListView.OverlayHeader
    snapMode: ListView.SnapToItem
    clip: true

    ScrollBar.vertical: ScrollBar {
        //height: 300//root.height - (headerHeight*2)
        //anchors.topMargin: root.headerHeight
        //anchors.bottomMargin: root.headerHeight
        //y: headerHeight
        //policy: ScrollBar.AlwaysOn
    }

    DebugTracer{}

    maximumFlickVelocity: 5000

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
                    Layout.preferredHeight: root.headerHeight
                    verticalAlignment: Text.AlignVCenter
                    text: root.listHeaders[index]
                }
            }
        }
    }


    delegate: Item {
        id: delegateRoot

        height: root.headerHeight
        width: root.width
        //anchors.left: parent.left
        //anchors.right: parent.right

        readonly property int rowIndex: index

        MouseArea {
            anchors.fill: parent

            enabled: root.selectable
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked: {
                root.currentIndex = delegateRoot.rowIndex
                root.itemClicked(mouse, delegateRoot.rowIndex)
            }
        }

        RowLayout {
            height: root.headerHeight

            Repeater {
                id: repeater
                model: root.listHeaders.length

                Item {
                    Layout.fillHeight: true
                    Layout.preferredWidth: root.listWidths[index]
                    Layout.margins: 2

                    Text {
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent

                        text: root.listValues[index](rowIndex)
                    }
                }
            }
        }
    }

    highlight: Rectangle {
        visible: root.selectable
        color: 'grey'
    }

    highlightMoveDuration: 100

}
