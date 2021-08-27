#include "player.h"
#include <QDebug>

Player::Player(QObject *parent) : QObject(parent),
    m_playing { false },
    m_play_pos { 0 }
{

}

const Sound::Sample& Player::get_next_sample()
{
    const Sound::Sample& s = m_sound_sample->get_next_sample();

    m_play_pos = m_sound_sample->get_read_pointer();
    return s;
}

void Player::set_sample(Sound *s)
{
    m_sound_sample = s;
}

void Player::set_playing(bool state)
{
    m_playing = state;
}
