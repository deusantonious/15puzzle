import QtQuick 2.0
GridView{
    id: root
    signal win()
    signal restart()
    width: parent.width
    height: parent.height - top_bar.height

    cellHeight: height / 4
    cellWidth: width / 4

    interactive: false
    anchors{
       top: top_bar.bottom
       left: parent.left
    }
    model: GameModel {
        id:game_model
        onWin:{
            root.win();
        }
        onRestart:{
            root.restart();
        }
    }
    delegate: Tile {
        id: tile_delegate
        width: view.cellWidth
        height: view.cellHeight
        tile_number: display
    }

}
