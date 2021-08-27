import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400
    property alias gestureArea: gestureArea
    property alias oscillograph: oscillograph
    property alias sound_image_repeater: sound_image_repeater

    title: qsTr("Home")

    Rectangle {
        anchors.fill: parent
        color: "White"

        MultiPointTouchArea {
            id: gestureArea
            anchors.fill: parent
        }
    }

    Repeater {
        id: sound_image_repeater
        anchors.fill: parent
        anchors.bottomMargin: 205

        model: sound_image.graph

        Rectangle {
            id: rectangle
            x: index
            y: parent.height * 0.5 - parent.height * 0.5 * modelData
            width: 1
            height: parent.height * modelData
            color: "Orange"
            border.width: 1
        }
    }

    Repeater {
        id: oscillograph
        anchors.fill: parent
        anchors.topMargin: 194

        model: samples.latest

        Rectangle {
            id: rectangle1
            x: index
            y: modelData > 0 ? parent.height / 2 : parent.height / 2 + modelData * 2000
            width: 1
            height: Math.abs(
                        modelData * 2000) //20 //+ parent.height //* modelData //.leftValue
            color: "#99999999"
        }
    }
}
