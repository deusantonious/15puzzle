import QtQuick 2.0

Text {
    id: root

    text: "You win!"
    color: "#001a1c"

    anchors {
        verticalCenter: parent.verticalCenter;
        left: parent.left;
        leftMargin: parent.width / 70;
    }

    font {
        pixelSize: Math.min(parent.height,parent.width) / 2;
        bold: true;
    }
}
