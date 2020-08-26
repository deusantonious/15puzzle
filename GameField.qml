import QtQuick 2.0
import GameFieldModel 1.0;

Item {
    id: root
    signal gameIsOver

    function shuffleTiles() {
        gameModel.shuffle();
    }

    GridView {
        id: puzzleView

        anchors.fill: root

        cellHeight: puzzleView.height / 4
        cellWidth: puzzleView.width / 4

        interactive: false

        model: GameModel {
            id:gameModel


        }

        delegate: Tile {
            id: tileDelegate

            width: puzzleView.cellWidth
            height: puzzleView.cellHeight

            tileNumber: display

            onClicked: {
                gameModel.swap(index);
            }
        }
        move: Transition {
            NumberAnimation {
                properties: "x, y"
                duration: 200
            }
        }
    }
}
