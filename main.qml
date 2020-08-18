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
        id: topBar

        width: root.width
        height:root.height/10

        onShuffleButtonClicked: gameField.shuffleTiles()
    }

    GameField {
        id: gameField

        width: root.width
        height: parent.height - topBar.height

        anchors{
            top: topBar.bottom
            left: parent.left
        }

        onGameIsOver: {
            topBar.isWinMassageOn = true
        }
    }

}
