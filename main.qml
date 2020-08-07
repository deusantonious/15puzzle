import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
Window {
    id: root
    title: qsTr("tag")
    color: "#e3e1e1"
    visible: true
    width: 720
    height: 720
    minimumHeight: 400
    minimumWidth: 400
    TopBar {
        id: top_bar
        width: root.width
        height:root.height/10
        onClicked: view.model.shuffle();
    }
    View {
        id: view
        onWin:{
            top_bar.show_win_massage();
        }
        onRestart: {
            top_bar.restart();
        }
    }

}
