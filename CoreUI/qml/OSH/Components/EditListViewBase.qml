import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OSH.Components 1.0
import OSH.js 1.0

RowLayout {
    id: root

    signal itemClicked(var mouse, int index)

    signal executeAdd

    property alias listView: listView
    property alias model: listView.model
    property alias listHeaders: listView.listHeaders
    property alias listWidths: listView.listWidths
    property alias listValues: listView.listValues

    ListViewBase {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true

        onItemClicked: root.itemClicked(mouse, index)
    }

    Button {
        Layout.preferredHeight: 48
        Layout.preferredWidth: 48
        icon.source: GFX.bigIcon("baseline_add_black_48dp.png")

        onClicked: root.executeAdd()
    }
}

