import QtQuick 2.0

MouseArea {
    id: root

    property string tileNumber: ""

    Rectangle {

        id: tile

        anchors {
            fill: parent
            margins:  Math.min(root.width, root.height) / 75
        }

        visible: tileNumber !== "0"
        color: "#78a85d"
        radius: Math.min(root.height, root.width) / 25

        Text {
            id: text

            anchors.centerIn: parent

            font {
                bold: true
                pixelSize: Math.min(root.height, root.width) / 2
            }

            color: "#001a1c"
            text: root.tileNumber
        }
    }
}
