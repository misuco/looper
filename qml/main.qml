import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Looper")

    FileForm {
        id: fileForm
        openButton.onPressed: {
            console.log("FileForm {openButton.onPressed}")
            fileDialog.visible = true
        }
        openButton.onClicked: {
            console.log("FileForm {openButton.onClicked}")
            fileDialog.visible = true
        }
        fileDialog.onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            player.load_sample( fileDialog.fileUrls )
            //sound_image.calculate_graph()
            stackView.pop()
            player.set_playing( true )
        }
        fileDialog.onRejected: {
            console.log("File Dialog Canceled")
            stackView.pop()
        }
    }


    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            font.family: "Roboto"
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }

        Rectangle {
            anchors {
                top: parent.top
                left: parent.left
            }
            width: parent.width * samples.peak
            height: parent.height * 0.1
            color: "Green"
        }

        /*
        Text {
            anchors.fill: parent
            text: " peak " + samples.peak
        }
        */


        Text {
            anchors {
                right: recButton.left
                top: parent.top
                bottom: parent.bottom
            }
            width: 200
            text: "Playing:" + player.playing;
        }


        Rectangle {
            id: playButton
            anchors.top: parent.top
            anchors.right: recButton.left
            width: parent.height
            height: parent.height
            color: player.playing ? "Red" : "Green"

            Text {
                anchors.fill: parent
                text: ">"
            }

            Component.onCompleted: player.factory_preset()

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if( player.playing ) {
                        player.set_playing( false )
                    } else {
                        player.set_playing( true )
                    }
                }
            }
        }

        Rectangle {
            id: recButton
            anchors.top: parent.top
            anchors.right: parent.right
            width: parent.height
            height: parent.height
            color: recorder.record_enable ? "Red" : "Green"

            Text {
                anchors.fill: parent
                text: "REC"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    recorder.record(!recorder.record_enable)
                    if(!recorder.record_enable) {
                        sound_image.set_width(sound_image_repeater.width);
                        sound_image_gesture.set_width(sound_image_repeater.width);
                        sound_image_gesture.set_height(sound_image_repeater.height);
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("FileDialog")
                width: parent.width
                onClicked: {
                    stackView.push("FileForm.ui.qml")
                    fileForm.fileDialog.visible = true
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Options")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "TracksView.qml"
        anchors.fill: parent
        /*
        onWidthChanged: {
            sound_image.set_width( width )
        }
        */
    }
}
