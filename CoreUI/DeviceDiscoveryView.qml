import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0

ViewBase {
    id: root

    ListView {
        id: deviceListView

        anchors.fill: parent

        model: DeviceDiscoveryManager.devices

        onModelChanged: {
            console.log("Model changed " + count)
        }

        header: Item {
            RowLayout {
                anchors.fill: parent

                Text {
                    Layout.preferredWidth: 300
                    text: qsTr("Name")
                }

                Text {
                    Layout.preferredWidth: 100
                    text: qsTr("Serial")
                }

                Text {
                    Layout.preferredWidth: 50
                    text: qsTr("Online")
                }

                Text {
                    text: qsTr("Last Ping")
                }
            }
        }

        delegate: Item {
            width: deviceListView.width
            height: 30

            DebugTracer{}

            RowLayout {
                anchors.fill: parent

                Text {
                    Layout.preferredWidth: 300
                    text: modelData.name
                }

                Text {
                    Layout.preferredWidth: 100
                    text: modelData.id
                }

                Text {
                    Layout.preferredWidth: 50
                    text: modelData.isOnline ? "Yes" : "No"
                }

                Text {
                    Layout.fillWidth: true
                    text: modelData.lastPing
                }
            }
        }
    }
}
