#include "player.h"
#include <QDebug>

void Player::load_sample(QString filename)
{
    m_sound_sample->init_from_file( filename );
}

Player::Player(QObject *parent) : QObject(parent),
    m_silence { .left=0, .right=0 },
    m_playing { false },
    m_play_pos { 0 }
{

}

const Sound::Sample& Player::get_next_sample()
{
    if( m_playing ) {
        const Sound::Sample& s = m_sound_sample->get_next_sample();
        //m_play_pos = m_sound_sample->get_read_pointer();
        //emit QmlPlayPosUpdated();
        return s;
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
