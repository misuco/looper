import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Looper")

    HomeForm {
        gestureArea.onPressed: {
            //samples.play(true);
            sound_image_gesture.pressed(touchPoints)
        }
        gestureArea.onUpdated: {
            sound_image_gesture.updated(touchPoints)
            //samples.update(touchPoints[0].x / (parent.width / 2));
        }
        gestureArea.onReleased: {
            //samples.play(false);
            sound_image_gesture.released(touchPoints)
        }
        gestureArea.onCanceled: {
            //samples.play(false);
            sound_image_gesture.canceled(touchPoints)
        }
        playButton.onClicked: {
            console.log("play clicked")
            player.set_playing( true )
        }
        stopButton.onClicked: {
            console.log("stop clicked")
            player.set_playing( false )
        }
    }

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
            sound_image.calculate_graph()
            stackView.push("HomeForm.ui.qml")
            player.set_playing( true )
        }
        fileDialog.onRejected: {
            console.log("File Dialog Canceled")
            stackView.push("HomeForm.ui.qml")
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
            text: "Recpos:" + recorder.record_pos + "\nPlaypos:" + player.play_pos + "\nPlaying:" + player.playing;
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
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
        onWidthChanged: {
            sound_image.set_width( width )
        }
    }
}
