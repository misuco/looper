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

#include "player.h"
#include "track.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>

void Player::factory_preset()
{
    load_sample_dir( ":/res/wav/loops/a82.wav" );
}

void Player::load_sample_dir(QString filename)
{
    filename = filename.replace("file:///","");

    QFileInfo file_info( filename );
    QDir file_dir = file_info.absoluteDir();

    foreach( auto file, file_dir.entryList() ) {

        if( file.endsWith( ".wav",  Qt::CaseInsensitive  ) ||
            file.endsWith( ".aif",  Qt::CaseInsensitive  ) ||
            file.endsWith( ".aiff", Qt::CaseInsensitive  ) ) {

            m_sound_sample=new Sound();

            m_sound_sample->init_from_file( file_dir.path() + "/" + file );
            m_sound_samples.append( m_sound_sample );

            Track * track = new Track( file );
            m_tracks.append( track );
        }
    }

    emit QmlTracksUpdated();

}

Player::Player(QObject *parent) : QObject(parent),
    m_silence { .left=0, .right=0 },
    m_playing { false },
    m_play_pos { 0 },
    m_update_counter { 0 }
{

}

const Sound::Sample& Player::get_next_sample()
{
    if( m_playing ) {
        /*
        const Sound::Sample& s = m_sound_sample->get_next_sample();
        return s;
        */

        bool update_track_status = false;
        m_update_counter++;
        if( m_update_counter == 500 ) {
            update_track_status = true;
            m_update_counter = 0;
        }

        m_next_sample.left = 0;
        m_next_sample.right = 0;

        int track=0;
        foreach( auto sample, m_sound_samples ) {
            const Sound::Sample& s = sample->get_next_sample();

            Track * t = dynamic_cast<Track *>(m_tracks.at( track ));
            if( t && !t->get_muted() ) {
                m_next_sample.left += s.left;
                m_next_sample.right += s.right;
            }

            if( update_track_status ) {
                double p = sample->get_read_pointer();
                double l = sample->get_size();
                double play_pos = p / l;
                if(t) t->set_play_pos( play_pos );
            }
            track++;
        }

        m_next_sample.left /= m_sound_samples.size();
        m_next_sample.right /= m_sound_samples.size();

        return m_next_sample;

        //m_play_pos = m_sound_sample->get_read_pointer();
        //emit QmlPlayPosUpdated();

    } else {
        return m_silence;
    }
}

void Player::set_sample(Sound *s)
{
    m_sound_sample = s;
}

void Player::set_playing(bool state)
{
    if( state == true && m_sound_sample->get_size() > 0 ) {
        m_playing = true;
    } else {
        m_playing = false;
    }
    emit QmlPlayingUpdated();
}
