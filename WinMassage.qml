import QtQuick 2.0

Text{
    id: root
    text:"You win!"
    anchors {
        verticalCenter: parent.verticalCenter;
        left: parent.left
        leftMargin: parent.width / 70;
    }
    font {
        pointSize: Math.min(parent.height,parent.width) / 1.5;
        bold: true
    }
    color: "#001a1c"
}
