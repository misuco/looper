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

#include "track.h"
#include <QDebug>

void Track::click( double x, double y)
{
    qDebug() << "click x:" << x << " y:" << y;
    m_muted = !m_muted;
    emit QmlMutedUpdated();
}

Track::Track(QString name, QObject *parent) : QObject(parent)
{
    m_name = name;
    m_muted = false;
}

void Track::set_play_pos(double p)
{
    m_play_pos = p;
    emit QmlPlayPosUpdated();
}

bool Track::get_muted()
{
    return m_muted;
}
