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

#ifndef SOUND_IMAGE_H
#define SOUND_IMAGE_H

#include <QObject>
#include "sample_graph_model.h"
#include "sound.h"

class Sound_image : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Sample_graph_model* graph MEMBER m_graph NOTIFY qml_image_updated)

public:
    Q_INVOKABLE void set_width(double w);
    Q_INVOKABLE void calculate_graph();

    explicit Sound_image(QObject *parent = nullptr);
    void set_sample(Sound * s);

signals:
    void qml_image_updated();

private:
    Sample_graph_model* m_graph;
    Sound* m_sample;
    double m_width;

};

#endif // SOUND_IMAGE_H
