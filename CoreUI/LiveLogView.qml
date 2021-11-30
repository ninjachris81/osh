import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0

ViewBase {
    id: root

    ListViewBase {
        id: logListView

        anchors.fill: parent

        model: LogManager.logs

        onModelChanged: {
            console.log("Log model changed " + count)
        }

        listHeaders: ["Name", "Type", "Message"]
        listWidths: [300, 100, -1]

        listValues: [
            function(rowIndex) { return DeviceDiscoveryManager.isKnownDevice(model[rowIndex].fullDeviceId) ? DeviceDiscoveryManager.getKnownDevice(model[rowIndex].fullDeviceId).name : model[rowIndex].name },
            function(rowIndex) { return model[rowIndex].type },
            function(rowIndex) { return model[rowIndex].msg },
        ]
    }
}
