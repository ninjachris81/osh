import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0
import OSH.Components 1.0
import OSH.js 1.0

ViewBase {
    id: root

    ListViewBase {
        id: valueListView

        anchors.fill: parent

        model: DatamodelManager.datamodel.values

        onModelChanged: {
            console.log("Value model changed " + count)
        }

        listHeaders: ["Full ID", "Is Valid", "S/R", "Value"]
        listWidths: [100, 100, 100, -1]

        listValues: [
            function(rowIndex) { return model[rowIndex].fullId },
            function(rowIndex) { return model[rowIndex].isValid },
            function(rowIndex) { return model[rowIndex].signalRate },
            function(rowIndex) { return Commons.formatValue(model[rowIndex]) }
        ]
    }
}
