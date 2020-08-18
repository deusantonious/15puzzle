import QtQuick 2.0
Item{
    id: root
    signal gameIsOver

    function shuffleTiles(){
        gameModel.shuffle();
    }

    GridView{
        id: puzzleView
        //make me work pls
        //property string tileNumber: display

        anchors.fill: root

        cellHeight: puzzleView.height / 4
        cellWidth: puzzleView.width / 4

        interactive: false

        model: GameModel {
            id:gameModel

            onGameIsOver:{
                root.gameIsOver()
            }
        }

        delegate: Tile {
            id: tileDelegate

            width: puzzleView.cellWidth
            height: puzzleView.cellHeight
            //y, and here
            tile_number: display

            onClicked: {
                gameModel.swap(index)
            }
        }
        move: Transition {
            NumberAnimation { properties: "x,y"
                duration: 200
            }
        }
    }
}
