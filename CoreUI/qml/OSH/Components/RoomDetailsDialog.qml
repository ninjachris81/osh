import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0
import OSH.js 1.0
import OSH.Components 1.0

Dialog {
    id: dialog
    title: qsTr("Edit Room")
    standardButtons: Dialog.Ok | Dialog.Cancel

    width: 1000
    height: 700

    property var knownRoom

    ColumnLayout {
        id: layout

        anchors.fill: parent

        TextInput {
            id: roomName
            text: knownRoom ? knownRoom.name : ""
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("Values")
        }


        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 200

            EditListViewBase {
                Layout.fillWidth: true
                Layout.fillHeight: true

                model: knownRoom ? knownRoom.values : null

                listHeaders: ["Full ID", "Is Valid", "S/R", "Value"]
                listWidths: [100, 100, 100, -1]
                listValues: [
                    function(rowIndex) { return model[rowIndex].fullId },
                    function(rowIndex) { return model[rowIndex].isValid },
                    function(rowIndex) { return model[rowIndex].signalRate },
                    function(rowIndex) { return Commons.formatValue(model[rowIndex]) }
                ]

                onExecuteAdd: {
                    knownRoom.addValue(availableValuesListView.model[availableValuesListView.currentIndex])
                }
            }

            ListViewBase {
                id: availableValuesListView
                Layout.preferredWidth: 120
                Layout.fillHeight: true

                model: DatamodelManager.datamodel.values

                listHeaders: ["Full ID"]
                listWidths: [100]
                listValues: [
                    function(rowIndex) { return model[rowIndex].fullId }
                ]

                selectable: true
            }
        }


        Label {
            text: qsTr("Actors")
        }


        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 200

            EditListViewBase {
                Layout.fillWidth: true
                Layout.fillHeight: true

                model: knownRoom ? knownRoom.actors : null

                listHeaders: ["Full ID", "Is Valid", "S/R", "Value"]
                listWidths: [100, 100, 100, -1]
                listValues: [
                    function(rowIndex) { return model[rowIndex].fullId },
                    function(rowIndex) { return model[rowIndex].isValid },
                    function(rowIndex) { return model[rowIndex].signalRate },
                    function(rowIndex) { return model[rowIndex].rawValue === undefined ? "Invalid" : model[rowIndex].rawValue }
                ]

                onExecuteAdd: {
                    knownRoom.addActor(availableActorsListView.model[availableActorsListView.currentIndex])
                }
            }

            ListViewBase {
                id: availableActorsListView
                Layout.preferredWidth: 120
                Layout.fillHeight: true

                model: DatamodelManager.datamodel.actors

                listHeaders: ["Full ID"]
                listWidths: [100]
                listValues: [
                    function(rowIndex) { return model[rowIndex].fullId }
                ]

                selectable: true
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }

    onAccepted: console.log("Ok clicked")
    onRejected: console.log("Cancel clicked")
}
