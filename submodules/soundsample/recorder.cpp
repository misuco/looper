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

#include "recorder.h"

void Recorder::record(bool enable)
{
    m_record_enable = enable;
    emit QmlRecordEnabledUpdated();
    if(!enable) {
        m_sound_sample->normalize();
    }
}

Recorder::Recorder(QObject * parent) : QObject(parent) ,
    m_record_enable { false },
    m_record_pos { 0 }
{

}

void Recorder::insert_sample( const Sound::Sample& s)
{
    if(m_record_enable) {
        m_sound_sample->insert_sample( s );
        //m_record_pos = m_sound_sample->get_write_pointer();
        //emit QmlRecordPosUpdated();
    }
}

void Recorder::set_sample(Sound *s)
{
    m_sound_sample = s;
}
