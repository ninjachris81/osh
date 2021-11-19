import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0

ViewBase {
    id: root

    ListView {
        id: taskListView

        anchors.fill: parent

        model: DatamodelManager.datamodel.values

        onModelChanged: {
            console.log("Value model changed " + count)
        }
        header: RowLayout {
                height: 50

                Text {
                    Layout.preferredWidth: 100
                    text: qsTr("Full ID")
                }

                Text {
                    Layout.preferredWidth: 100
                    text: qsTr("Is valid")
                }

                Text {
                    text: qsTr("Raw Value")
                }
        }

        delegate: Item {
            width: taskListView.width
            height: 30

            DebugTracer{}

            RowLayout {
                height: 30

                Text {
                    Layout.preferredWidth: 100
                    text: modelData.fullId
                }

                Text {
                    Layout.preferredWidth: 100
                    text: modelData.isValid
                }

                Text {
                    text: modelData.rawValue === undefined ? "Invalid" : modelData.rawValue
                }
            }
        }

    }
}
