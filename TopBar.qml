import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle{
    id: root

    property alias isWinMassageOn: winMassageLoader.active

    signal shuffleButtonClicked

    color: "#8bb0ba"

    Loader {
        id: winMassageLoader

        anchors.fill: root
        source: "WinMassage.qml"
        active: false
    }

    Button {
        id: shuffleButton

        height: parent.height * 0.9
        width: parent.width * 0.2

        anchors{
            verticalCenter: root.verticalCenter
            right: root.right
            rightMargin: root.width / 75
        }

        onClicked:{
            root.shuffleButtonClicked()
            isWinMassageOn = false
        }

        text:"shuffle"

        Text {

            color: "#001a1c"
            anchors.centerIn: parent
            font {
               pointSize: Math.min(parent.height, parent.width )/ 4
               bold: true
            }
        }
    }
}
