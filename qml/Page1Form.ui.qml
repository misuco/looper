import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    anchors.fill: parent

    title: qsTr("Playarea")

    Dial {
        id: dial
        x: 107
        y: 112
        width: 176
        height: 181
    }

    Dial {
        id: dial1
        x: 332
        y: 112
        width: 195
        height: 181
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

