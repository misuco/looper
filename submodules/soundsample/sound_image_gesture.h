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

#ifndef SOUND_IMAGE_GESTURE_H
#define SOUND_IMAGE_GESTURE_H

#include <QObject>
#include <QMap>
#include "player.h"
#include "sound.h"

class Sound_image_gesture : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void set_width(double w);
    Q_INVOKABLE void set_height(double h);

    Q_INVOKABLE void pressed(QVariant x);
    Q_INVOKABLE void updated(QVariant x);
    Q_INVOKABLE void released(QVariant x);
    Q_INVOKABLE void canceled(QVariant x);

    explicit Sound_image_gesture(Player * p, QObject *parent = nullptr);

    void set_sample(Sound *s);

private:
    Player * m_player;
    Sound * m_sound_sample;

    // indexes of metaproperties
    const int c_point_id_index = 1;
    const int c_x_index = 4;
    const int c_y_index = 5;
    struct TouchPoint {
        double x;
        double y;
    };

    double m_width;
    double m_height;

    QMap<int,TouchPoint> m_touched;
    int m_touch_count;

    void calculate();

};

#endif // SOUND_IMAGE_GESTURE_H
