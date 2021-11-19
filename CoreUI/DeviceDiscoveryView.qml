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
            console.log("DD model changed " + count)
        }

        header: RowLayout {
                height: 30

                Text {
                    Layout.preferredWidth: 300
                    text: qsTr("ID")
                }

                Text {
                    Layout.preferredWidth: 300
                    text: qsTr("ServiceID")
                }

                Text {
                    Layout.preferredWidth: 200
                    text: qsTr("SessionId")
                }

                Text {
                    Layout.preferredWidth: 200
                    text: qsTr("Name")
                }

                Text {
                    Layout.preferredWidth: 50
                    text: qsTr("Online")
                }

                Text {
                    text: qsTr("Last Ping")
                }
        }

        delegate: Item {
            width: deviceListView.width
            height: 30

            DebugTracer{}

            RowLayout {
                height: 30


                Text {
                    Layout.preferredWidth: 300
                    text: modelData.id
                }

                Text {
                    Layout.preferredWidth: 300
                    text: modelData.serviceId
                }

                Text {
                    Layout.preferredWidth: 200
                    text: modelData.sessionId
                }

                Text {
                    Layout.preferredWidth: 200
                    text: modelData.name
                }

                Text {
                    Layout.preferredWidth: 50
                    text: modelData.isOnline
                }

                Text {
                    text: modelData.lastPing
                }
            }
        }
    }
}
