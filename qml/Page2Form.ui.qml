import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400
    property alias bufferSize: bufferSize

    title: qsTr("Page 2")

    Label {
        text: qsTr("Buffer Size")
        anchors.verticalCenterOffset: -166
        anchors.horizontalCenterOffset: -232
        anchors.centerIn: parent
    }

    Slider {
        id: bufferSize
        x: 36
        y: 65
        width: 442
        height: 48
        stepSize: 1
        to: 10
        snapMode: Slider.SnapAlways
        value: 1
    }
}
