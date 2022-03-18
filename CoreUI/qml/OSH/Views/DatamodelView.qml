import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0
import OSH.Components 1.0

ViewBase {
    id: root

    RoomDetailsDialog {
        id: roomDetailsDialog
        anchors.centerIn: root
    }

    EditListViewBase {
        id: knownRoomsView

        anchors.fill: parent

        model: DatamodelManager.datamodel.knownRooms

        listHeaders: ["ID", "Name", "Values", "Actors"]
        listWidths: [100, 100, 100, -1]

        listValues: [
            function(rowIndex) { return model[rowIndex].id },
            function(rowIndex) { return model[rowIndex].name },
            function(rowIndex) { return model[rowIndex].values.length },
            function(rowIndex) { return model[rowIndex].actors.length }
        ]

        Menu {
            id: contextMenu
            property int rowIndex

            Action {
                text: qsTr('Edit')
                onTriggered: {
                    console.info("Edit room")
                    roomDetailsDialog.knownRoom = DatamodelManager.datamodel.knownRooms[contextMenu.rowIndex]
                    roomDetailsDialog.open()
                }
            }
            Action {
                text: qsTr('Delete')
                onTriggered: {
                    console.info("Delete room")
                }
            }
        }

        listView.selectable: true

        onItemClicked: {
            if (mouse.button === Qt.RightButton) {
                contextMenu.rowIndex = index
                contextMenu.popup()
            }
        }
    }

}
