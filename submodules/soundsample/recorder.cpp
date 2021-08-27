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
        m_record_pos = m_sound_sample->get_write_pointer();
        emit QmlRecordPosUpdated();
    }
}

void Recorder::set_sample(Sound *s)
{
    m_sound_sample = s;
}
