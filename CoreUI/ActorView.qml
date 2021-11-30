import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0

ViewBase {
    id: root

    ListViewBase {
        id: taskListView

        anchors.fill: parent

        model: DatamodelManager.datamodel.actors

        onModelChanged: {
            console.log("Actor model changed " + count)
        }

        listHeaders: ["Full ID", "Is Valid", "Signal Rate", "Raw Value"]
        listWidths: [100, 100, 100, -1]
        listValues: [
            function(rowIndex) { return model[rowIndex].fullId },
            function(rowIndex) { return model[rowIndex].isValid },
            function(rowIndex) { return model[rowIndex].signalRate },
            function(rowIndex) { return model[rowIndex].rawValue === undefined ? "Invalid" : model[rowIndex].rawValue }
        ]
    }
}
