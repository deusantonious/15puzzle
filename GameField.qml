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

        cellHeight: puzzleView.height / model.dimention
        cellWidth: puzzleView.width / model.dimention

        interactive: false

        model: GameModel {
            id:gameModel

            onIsGameOverChanged: {
                gameIsOver();
            }
        }

        delegate: Tile {
            id: tileDelegate

            width: puzzleView.cellWidth
            height: puzzleView.cellHeight

            hiddenValue: hiddenNumberValue
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
