import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH 1.0

ViewBase {
    id: root

    ListView {
        id: taskListView

        anchors.fill: parent

        model: DatamodelManager.datamodel.processorTasks

        onModelChanged: {
            console.log("Task model changed " + count)
        }
        header: RowLayout {
                height: 50

                Text {
                    Layout.preferredWidth: 100
                    text: qsTr("Name")
                }

                Text {
                    Layout.preferredWidth: 100
                    text: qsTr("Schedule Interval")
                }

                Text {
                    Layout.preferredWidth: 100
                    text: qsTr("Last Execution")
                }

                Text {
                    Layout.preferredWidth: 100
                    text: qsTr("Last result")
                }

                Text {
                    text: qsTr("Script Code")
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
                    text: modelData.id
                }

                Text {
                    Layout.preferredWidth: 100
                    text: modelData.scheduleInterval
                }

                Text {
                    Layout.preferredWidth: 100
                    text: modelData.lastExecution
                }

                Text {
                    Layout.preferredWidth: 100
                    text: modelData.lastResult
                }

                Text {
                    text: modelData.scriptCode
                }
            }
        }

    }
}
