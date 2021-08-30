import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    anchors.fill: parent

    property alias stopButton: stopButton
    property alias playButton: playButton
    property alias gestureArea: gestureArea
    property alias oscillograph: oscillograph
    property alias sound_image_repeater: sound_image_repeater

    title: qsTr("Home")

    Rectangle {
        anchors.fill: parent
        anchors.bottomMargin: 205
        color: "White"

        MultiPointTouchArea {
            id: gestureArea
            anchors.fill: parent
            anchors.bottomMargin: 205
        }
    }

    Rectangle {
        y: 0
        width: parent.width
        height: parent.height / 3
        color: "orange"
        Repeater {
            id: sound_image_repeater
            width: parent.width
            height: parent.height / 3

            model: sound_image.graph

            Rectangle {
                id: rectangle
                x: index
                y: parent.height * 0.5 - parent.height * 0.5 * modelData
                width: 1
                height: parent.height * modelData
                color: "Green"
                border.width: 1
            }
        }
    }

    Rectangle {
        id: oscillograph
        y: parent.height / 3
        width: parent.width
        height: parent.height / 3
        color: "yellow"

        Repeater {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height / 3

            model: samples.latest

            Rectangle {
                id: rectangle1
                x: index
                y: parent.height * 0.5 - parent.height * 0.5 * modelData
                //modelData > 0 ? parent.height / 2 : parent.height / 2 + modelData * 2000
                width: 1
                height: parent.height * modelData
                //Math.abs(modelData * 2000) //20 //+ parent.height //* modelData //.leftValue
                color: "orange"
            }
        }
    }

    Button {
        id: playButton
        x: 15
        y: 345
        text: qsTr("PLAY")
    }

    Button {
        id: stopButton
        x: 107
        y: 345
        text: qsTr("STOP")
    }
}
