import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0

ViewBase {
    id: root

    ListViewBase {
        id: deviceListView

        anchors.fill: parent

        model: DeviceDiscoveryManager.devices

        onModelChanged: {
            console.log("DD model changed " + count)
        }

        listHeaders: ["DeviceID", "ServiceID", "Name", "Online", "Last Ping"]
        listWidths: [300, 300, 200, 50, -1]

        listValues: [
            function(rowIndex) { return model[rowIndex].id },
            function(rowIndex) { return model[rowIndex].serviceId },
            function(rowIndex) { return model[rowIndex].name },
            function(rowIndex) { return model[rowIndex].isOnline },
            function(rowIndex) { return model[rowIndex].lastPing }
        ]
    }
}
