import QtQuick 2.0

MouseArea {
    id: root

    property string tileNumber: ""
    property string hiddenValue: ""

    Rectangle {

        id: tile

        anchors {
            fill: parent
            margins:  Math.min(root.width, root.height) * 0.02 //0.02 - my margin koef
        }

        visible: tileNumber !== hiddenValue
        color: "#78a85d"
        radius: Math.min(root.height, root.width) * 0.04

        Text {
            id: text

            anchors.centerIn: parent

            font {
                bold: true
                pixelSize: Math.min(root.height, root.width) * 0.5
            }

            color: "#001a1c"
            text: root.tileNumber
        }
    }
}
