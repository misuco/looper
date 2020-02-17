#include "player.h"
#include <QDebug>

Player::Player(QObject *parent) : QObject(parent),
    m_playing { false }
{

}

double Player::get_next_sample(int channel)
{
    if(m_playing && channel < s_channel_count) {
        return m_sound_samples[channel]->get_next_sample();
    } else {
        return 0;
    }
}

void Player::set_sample(SoundSample *s, int channel)
{
    if(channel<s_channel_count) {
        m_sound_samples[channel] = s;
    }
}

void Player::set_playing(bool state)
{
    m_playing = state;
}
