import QtQuick 2.0
import QtQuick.Controls 2.12
Rectangle{
    id: root
    signal clicked()
    function show_win_massage(){
        win_massage_loader.source = "WinMassage.qml"
    }
    function restart(){
        win_massage_loader.source = ""
    }
    color: "#8bb0ba"
    Loader {
        id: win_massage_loader
        anchors.fill: root
        source: ""
    }
    Button {
        id: shuffle_button
        height: parent.height * 0.9
        width: parent.width * 0.2
        anchors{
            verticalCenter: root.verticalCenter;
            right: root.right;
            rightMargin: root.width / 75;
        }
        onClicked:{
            root.clicked();
        }
        Text {
            text:"shuffle"
            color: "#001a1c"
            anchors.centerIn: parent
            font{
               pointSize: Math.min(parent.height, parent.width )/ 4;
               bold: true;
            }
        }
    }
}
