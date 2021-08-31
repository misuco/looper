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

#include <QDebug>
#include "sound_image.h"

void Sound_image::set_width(double w)
{
    qDebug() << "Sound_image::set_width " << w;
    m_width = w;
    calculate_graph();
}

Sound_image::Sound_image(QObject *parent) : QObject(parent),
    m_graph { new Sample_graph_model(this) } ,
    m_sample { nullptr }
{

}

void Sound_image::set_sample(Sound *s)
{
    m_sample = s;
    calculate_graph();
}

void Sound_image::calculate_graph()
{
    if(m_sample) {
        double samples_per_pixel = m_sample->get_size() / m_width;
        double pixel_sample_index = 0;
        double pixel_sample_value = 0;
        int pixels = 0;
        m_graph->reset();
        emit qml_image_updated();
        for(int i=0;i<m_sample->get_size();i++) {
            pixel_sample_value = qMax(pixel_sample_value, qAbs(m_sample->get_sample_at(i).left));
            pixel_sample_index+=1;
            if(pixel_sample_index>=samples_per_pixel) {
                pixels ++;

                //qDebug() << "Sound_image::calculate_graph insert " << pixel_sample_value << " " << pixels;

                m_graph->append(pixel_sample_value);
                emit qml_image_updated();
                pixel_sample_value = 0;
                pixel_sample_index -= samples_per_pixel;
            }
        }
    }
}
