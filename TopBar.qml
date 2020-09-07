import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: root

    property alias isWinMessageOn: winMessageLoader.active

    signal shuffleButtonClicked

    color: "#8bb0ba"

    Loader {
        id: winMessageLoader

        anchors.fill: root
        source: "WinMessage.qml"
        active: false
    }

    Button {
        id: shuffleButton

        height: parent.height * 0.9
        width: parent.width * 0.2

        anchors {
            verticalCenter: root.verticalCenter
            right: root.right
            rightMargin: root.width * 0.02 //0.02 - my margin koef
        }

        background: Rectangle {
            anchors.fill: shuffleButton
            color: "#e3e1e1"
        }

        text: "<font color='#001a1c'><b>shuffle</b></font>"
        font.pixelSize: shuffleButton.height * 0.5

        onClicked: {
            root.shuffleButtonClicked();
            isWinMessageOn = false;
        }
    }
}
