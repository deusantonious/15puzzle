import QtQuick 2.0

MouseArea{
    id: root

    property string tile_number: ""

    Rectangle {

        id: tile

        anchors {
            fill: parent
            margins:  Math.min(root.width,root.height) / 75
        }

        visible: display !== "0"
        color: "#78a85d"
        radius: Math.min(height,width) / 25

        Text {
            id: text

            anchors.centerIn: parent

            font{
                bold: true
                pointSize: Math.min(parent.height,parent.width) / 2;
            }

            color: "#001a1c"
            text: root.tile_number
        }
    }
}
