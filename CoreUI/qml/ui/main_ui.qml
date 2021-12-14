import QtQuick 2.0
import QtQuick.Controls 2.12

import OSH 1.0
import OSH.Components.Visual 1.0
import OSH.js 1.0

Item {
    id: root

    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ededed"; }
            GradientStop { position: 1.0; color: "#cccccc"; }
        }

        VisualHouse {
            anchors.fill: parent
            anchors.margins: 20

            SwipeView {
                id: floorStackView
                anchors.fill: parent

                orientation: Qt.Vertical

                readonly property int componentCount: 4
                property int loadedComponents: 0
                readonly property int correctedCurrentIndex: count - currentIndex - 1

                onCorrectedCurrentIndexChanged: {
                    if (loadedComponents > 0) {
                        VisualStateManager.currentFloor = correctedCurrentIndex
                    }
                }

                function setCorrectedCurrentIndex(i) {
                    currentIndex = count - i - 1
                }

                Loader {
                    //active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                    active: SwipeView.isCurrentItem
                    sourceComponent: Floor3 {
                        Component.onCompleted: floorStackView.loadedComponents++
                    }
                }

                Loader {
                    //active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                    active: SwipeView.isCurrentItem
                    sourceComponent: Floor2 {
                        Component.onCompleted: floorStackView.loadedComponents++
                    }
                }

                Loader {
                    //active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                    active: SwipeView.isCurrentItem
                    sourceComponent: Floor1 {
                        Component.onCompleted: floorStackView.loadedComponents++
                    }
                }

                Loader {
                    //active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                    active: SwipeView.isCurrentItem
                    sourceComponent: Floor0 {
                        Component.onCompleted: floorStackView.loadedComponents++
                    }
                }

                Connections {
                    target: VisualStateManager

                    function onCurrentFloorChanged() {
                        floorStackView.setCorrectedCurrentIndex(VisualStateManager.currentFloor)
                    }
                }

                Component.onCompleted: {
                    setCorrectedCurrentIndex(VisualStateManager.currentFloor)
                }
            }
        }

        MouseArea {
            id: backgroundMouseArea
            anchors.fill: parent

            onClicked: {
                floorMenu.isOpen = false
            }
            enabled: floorMenu.isOpen
        }
    }

    VisualStatusBar {
        id: statusBar
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 2
        anchors.topMargin: 2

        onTriggerFloorMenu: {
            floorMenu.isOpen = true
        }
    }

    VisualFloorMenu {
        id: floorMenu
        x: statusBar.floorLabelLeft
        width: statusBar.floorLabelWidth
        anchors.top: statusBar.bottom
        //anchors.topMargin: -4
    }

}
