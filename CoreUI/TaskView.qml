import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0

ViewBase {
    id: root

    ListViewBase {
        id: taskListView

        anchors.fill: parent

        model: DatamodelManager.datamodel.processorTasks

        onModelChanged: {
            console.log("Task model changed " + count)
        }

        listHeaders: ["Name", "Schedule Interval", "Last Execution", "Last Result", "Script Code"]
        listWidths: [100, 100, 100, 100, -1]

        listValues: [
            function(rowIndex) { return model[rowIndex].id },
            function(rowIndex) { return model[rowIndex].scheduleInterval === 0 ? "(default)" : model[rowIndex].scheduleInterval },
            function(rowIndex) { return model[rowIndex].lastExecution },
            function(rowIndex) { return model[rowIndex].lastResult === undefined ? "Invalid" : model[rowIndex].lastResult },
            function(rowIndex) { return model[rowIndex].scriptCode },
        ]
    }
}
