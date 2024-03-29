/**
 *
 * Copyright (C) 2021 Claudio Zopfi
 *
 * This file is part of the Looper project ( https://github.com/misuco/looper )
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 320
    height: 240
    title: qsTr("Looper")

    Rectangle {
        anchors.fill: parent
        color: "White"

        MultiPointTouchArea {
            anchors.fill: parent
            onPressed: {
                //samples.play(true);
                sound_image_gesture.pressed(touchPoints);
            }
            onUpdated: {
                sound_image_gesture.updated(touchPoints);
                //samples.update(touchPoints[0].x / (parent.width / 2));
            }
            onReleased: {
                //samples.play(false);
                sound_image_gesture.released(touchPoints);
            }
            onCanceled: {
                //samples.play(false);
                sound_image_gesture.canceled(touchPoints);
            }
        }
    }

    Repeater {
        id: sound_image_repeater
        anchors.fill: parent

        model: sound_image.graph

        Rectangle {
            x: index
            y: parent.height * 0.5 - parent.height * 0.5 * modelData
            width: 1
            height:  parent.height * modelData
            color: "Orange"
        }
    }

    Repeater {
        id: oscillograph
        anchors.fill: parent

        model: samples.latest

        Rectangle {
            x: index
            y: modelData>0 ? parent.height / 2 : parent.height / 2 + modelData * 2000
            width: 1
            height: Math.abs(modelData * 2000) //20 //+ parent.height //* modelData //.leftValue
            color: "#99999999"
        }
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

    Text {
        anchors.fill: parent
        text: " peak " + samples.peak
    }

    Rectangle {
        id: recButton
        x: 244
        y: 165
        width: 62
        height: 56
        color: recorder.record_enable ? "Red" : "Green"
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
