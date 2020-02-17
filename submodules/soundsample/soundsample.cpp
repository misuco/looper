#include "soundsample.h"
#include <QDebug>

SoundSample::SoundSample() :
    m_buffer_size { 0 } ,
    m_buffer { nullptr } ,
    m_write_pointer { 0 } ,
    m_read_pointer { 0 } ,
    m_read_speed { 1 } ,
    m_previous_sample { 0 } ,
    m_loop_length { 0 } ,
    m_start_point { 0 }
{

}

SoundSample::~SoundSample()
{
    if(m_buffer_size>0) {
        delete m_buffer;
    }
}

void SoundSample::init(int size)
{
    if(m_buffer_size>0) {
        delete m_buffer;
    }
    m_buffer_size = size;
    m_buffer = new double[size];
    m_loop_length = size;
}

void SoundSample::insert_sample(double value)
{
    if(m_buffer_size>0) {
        if(m_write_pointer >= m_buffer_size) {
            m_write_pointer = 0;
        }
        m_buffer[m_write_pointer] = value;
        m_write_pointer++;
        m_loop_length = qMax(static_cast<double>(m_write_pointer),m_loop_length);
    }
    //qDebug() << "SoundSample::insert_sample " << m_write_pointer;
}

double SoundSample::get_next_sample()
{
    /*
    double m_read_pointer_overflow = m_read_pointer - m_buffer_size;
    if( m_read_pointer_overflow >= 0 ) {
        m_read_pointer = m_read_pointer_overflow;
    }
    */

    if(m_read_pointer > m_buffer_size) {
        m_read_pointer = m_start_point;
    }

    int m_read_pointer_int = static_cast<int>(m_read_pointer);
    double nextSample = m_buffer[m_read_pointer_int];
    m_read_pointer += m_read_speed;
    //qDebug() << "SoundSample::get_next_sample " << m_read_pointer << " " << nextSample;
    return nextSample;
}

void SoundSample::set_read_speed(double s)
{
    qDebug() << "SoundSample::set_read_speed " << s;
    m_read_speed = s;
}

void SoundSample::setLoopLength(double l)
{
    if(l+m_start_point > m_buffer_size) {
        m_loop_length = m_buffer_size - m_start_point;
    } else {
        m_loop_length = l;
    }
}

void SoundSample::set_start_point(double p)
{
    if(p+m_loop_length > m_buffer_size) {
        m_start_point = m_buffer_size - m_loop_length;
    } else {
        m_start_point = p;
    }
}

int SoundSample::get_size()
{
    return m_buffer_size;
}

double SoundSample::get_sample_at(int i)
{
    double value = 0;
    if(i<m_buffer_size) {
        value = m_buffer[i];
    }
    return value;
}

void SoundSample::normalize()
{
    double max_peak = 0;
    for(int i=0;i<m_buffer_size;i++) {
        max_peak = qMax(max_peak,qAbs(m_buffer[i]));
    }
    double normalize_factor = 1 / max_peak;
    for(int i=0;i<m_buffer_size;i++) {
        m_buffer[i] = m_buffer[i] * normalize_factor;
    }
}
