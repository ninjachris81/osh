pragma Singleton
import QtQuick 2.12

QtObject {
    id: root

    readonly property var floorNames: [qsTr("Keller"), qsTr("EG"), qsTr("OG"), qsTr("Dach")]
    readonly property string currentFloorName: floorNames[currentFloor]
    property int currentFloor: 2

}
