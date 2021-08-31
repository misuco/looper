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

#include "sound_image_gesture.h"
#include <QMetaProperty>
#include <QDebug>

Sound_image_gesture::Sound_image_gesture(Player * p, QObject *parent) : QObject(parent) ,
    m_player {p} ,
    m_width { 0 } ,
    m_height { 0 } ,
    m_touch_count { 0 }
{

}

void Sound_image_gesture::set_width(double w)
{
    m_width = w;
}

void Sound_image_gesture::set_height(double h)
{
    m_height = h;
}

void Sound_image_gesture::pressed(QVariant x)
{
    updated(x);
}

void Sound_image_gesture::updated(QVariant x)
{
    QList<QVariant> y = x.toList();
    for(auto const & z : y ) {
        QObject * o = z.value<QObject*>();
        const QMetaObject * mo = o->metaObject();
        QMetaProperty mpId = mo->property(c_point_id_index);
        int pointId = mpId.read(o).toInt();

        //qDebug() << "Sound_image_gesture::updated " << pointId;
        TouchPoint p;
        QMetaProperty mpX = mo->property(c_x_index);
        p.x = mpX.read(o).toInt();
        QMetaProperty mpY = mo->property(c_y_index);
        p.y = mpY.read(o).toInt();

        m_touched.insert(pointId,p);
    }

    /*
    for(auto const & z : y ) {
        QObject * o = z.value<QObject*>();
        const QMetaObject * mo = o->metaObject();

        qDebug() << " - " << mo->className();
        for(int j=0;j< mo->propertyCount();j++) {
            QMetaProperty mp = mo->property(j);
            qDebug() << " - " << j << " " << mp.name() << " " << mp.read(o);
        }

         -  QQuickTouchPoint
         -  0   objectName   QVariant(QString, "")
         -  1   pointId   QVariant(int, 33554433)
         -  2   uniqueId   QVariant(QPointingDeviceUniqueId, )
         -  3   pressed   QVariant(bool, true)
         -  4   x   QVariant(double, 136.168)
         -  5   y   QVariant(double, 87.924)
         -  6   ellipseDiameters   QVariant(QSizeF, QSizeF(0, 0))
         -  7   pressure   QVariant(double, 1)
         -  8   rotation   QVariant(double, 0)
         -  9   velocity   QVariant(QVector2D, QVector2D(0, 0))
         -  10   area   QVariant(QRectF, QRectF(136.168,87.924 0x0))
         -  11   startX   QVariant(double, 74.7332)
         -  12   startY   QVariant(double, 84.7915)
         -  13   previousX   QVariant(double, 135.685)
         -  14   previousY   QVariant(double, 87.6831)
         -  15   sceneX   QVariant(double, 136.168)
         -  16   sceneY   QVariant(double, 87.924)
         */
    m_touch_count = m_touched.size();
    calculate();
}

void Sound_image_gesture::released(QVariant x)
{
    QList<QVariant> y = x.toList();
    for(auto const & z : y ) {
        QObject * o = z.value<QObject*>();
        const QMetaObject * mo = o->metaObject();
        QMetaProperty mpId = mo->property(c_point_id_index);
        int pointId = mpId.read(o).toInt();
        m_touched.remove(pointId);
    }
    m_touch_count = m_touched.size();
    calculate();
}

void Sound_image_gesture::canceled(QVariant x)
{
    released(x);
}

void Sound_image_gesture::set_sample(Sound *s)
{
    m_sound_sample = s;
}

void Sound_image_gesture::calculate()
{
    if(m_width > 0 && m_height > 0) {
        if(m_touch_count>1) {

            TouchPoint p1 = m_touched.first();
            TouchPoint p2 = m_touched.last();

            double x_diff = qAbs(p1.x - p2.x);
            double y_avg_norm = 1 - (p1.y + p2.y) / 2 / m_height;
            double x_left = qMin(p1.x , p2.x);
            double y_diff_factor = 1;

            if(y_avg_norm > 0.5) {
                y_diff_factor = y_avg_norm * 2;
            } else {
                y_diff_factor =  y_avg_norm;
            }

            //qDebug() << "Player::calculate p1.y " << p1.y << " p2.y "  << p2.y << " y_avg_norm " << y_avg_norm << " y_diff_factor " << y_diff_factor << " x_left " << x_left << " m_width " << m_width << " m_height " << m_height;

            double loop_length = x_diff / m_width * m_sound_sample->get_size();
            double start_point = x_left / m_width * m_sound_sample->get_size();
            double read_speed = y_diff_factor;
            m_sound_sample->setLoopLength(loop_length);
            m_sound_sample->set_start_point(start_point);
            m_sound_sample->set_read_speed(read_speed);

            m_player->set_playing(true);
        } else {
            m_player->set_playing(false);
        }
    }
}
