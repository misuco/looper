#include "recorder.h"

void Recorder::record(bool enable)
{
    m_record_enable = enable;
    emit QmlRecordEnabledUpdated();
    if(!enable) {
        for(int channel=0;channel<s_channel_count;channel++) {
            m_sound_samples[channel]->normalize();
        }
    }
}

Recorder::Recorder(QObject * parent) : QObject(parent) ,
    m_record_enable { false }
{

}

void Recorder::insert_sample(double value, int channel)
{
    if(m_record_enable) {
        if(channel<s_channel_count) {
            m_sound_samples[channel]->insert_sample(value);
        }
    }
}

void Recorder::set_sample(SoundSample *s, int channel)
{
    if(channel<s_channel_count) {
        m_sound_samples[channel] = s;
    }
}
