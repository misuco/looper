import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Page {
    title: qsTr("Fileform")

    property alias fileDialog: fileDialog
    property alias openButton: openButton

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
    }

    Button {
        id: openButton
        x: 225
        y: 202
        width: 191
        height: 77
        text: "Open"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

