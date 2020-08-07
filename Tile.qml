import QtQuick 2.0
Item{
    id: root
    property string tile_number: ""
    Rectangle {
        id: tile
        parent: view

        x: root.x;
        y: root.y

        width: root.width - Math.min(root.width,root.width) / 50
        height: root.height - Math.min(root.width,root.width) / 50

        visible: display !== "0"
        color: "#78a85d"
        radius: Math.min(height,width) / 25

        Text {
            id: text
            anchors.centerIn: parent
            font{ bold: true; pointSize: Math.min(parent.height,parent.width) / 2; }
            color: "#001a1c"
            text: root.tile_number
        }
        MouseArea {
            id: mouse_area
            anchors.fill: parent
            onClicked: {
                view.model.swap(index);
                view.model.isGameOver();
            }
        }
        Behavior on x { NumberAnimation { duration: 200; } }
        Behavior on y { NumberAnimation { duration: 200; } }
    }
}
