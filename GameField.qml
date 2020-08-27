import QtQuick 2.0
import GameFieldModel 1.0;

Item {
    id: root
    signal gameIsOver

    function shuffleTiles() {
        gameModel.shuffleTiles();
    }

    GridView {
        id: puzzleView

        anchors.fill: root

        cellHeight: puzzleView.height / gameModel.dimention
        cellWidth: puzzleView.width / gameModel.dimention

        interactive: false

        model: GameModel {
            id:gameModel

            onGameOver: {
                gameIsOver();
            }
        }

        delegate: Tile {
            id: tileDelegate

            width: puzzleView.cellWidth
            height: puzzleView.cellHeight

            hiddenValue: gameModel.hiddenValue
            tileNumber: display

            onClicked: {
                gameModel.move(index);
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
