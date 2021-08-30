#include "sound.h"
#include <QDebug>
#include <QFile>
#include <AudioFile.h>

Sound::Sound() :
    m_buffer_size { 0 } ,
    m_buffer { nullptr } ,
    m_write_pointer { 0 } ,
    m_read_pointer { 0 } ,
    m_read_speed { 1 } ,
    //m_previous_sample { 0 } ,
    m_loop_length { 0 } ,
    m_start_point { 0 }
{

}

Sound::~Sound()
{
    if(m_buffer_size>0) {
        delete[] m_buffer;
    }
}

bool Sound::init_from_file(QString filename)
{
    filename = filename.replace("file:///","");
    std::string f = filename.toStdString();
    QFile file( filename );
    qDebug() << "Opening " << filename << " exists " << file.exists();

    file.open( QIODevice::ReadOnly);
    QByteArray bytearray = file.readAll();
    file.close();
    qDebug() << "read " << bytearray.size() << " bytes ";

    if( bytearray.size() > 0 ) {
        std::vector<uint8_t> audio_vector;
        for(int i=0;i<bytearray.size();i++) {
            audio_vector.push_back(bytearray.at(i));
        }

        AudioFileFormat audioFileFormat;
        AudioFile<double> audio_file;
        audioFileFormat = audio_file.determineAudioFileFormat ( audio_vector );

        if (audioFileFormat == AudioFileFormat::Wave)
        {
            qDebug() << "Detected wav format";
            audio_file.decodeWaveFile( audio_vector );
        }
        else if (audioFileFormat == AudioFileFormat::Aiff)
        {
            qDebug() << "Detected aif format";
            audio_file.decodeAiffFile( audio_vector );
        }

        qDebug() << "bits per sample " << audio_file.getBitDepth();
        qDebug() << "channel number " << audio_file.getNumChannels();
        qDebug() << "frame number " << audio_file.getNumSamplesPerChannel();
        qDebug() << "sample rate " << audio_file.getSampleRate();

        m_buffer_size = audio_file.getNumSamplesPerChannel();
        m_loop_length = m_buffer_size;

        m_buffer = new Sound::Sample[m_buffer_size];

        for(int i=0;i<m_buffer_size;i++) {
            m_buffer[i].left = audio_file.samples[0][i];
            m_buffer[i].right = audio_file.samples[1][i];
        }

        return true;
    }

    return false;
}

void Sound::init(int size)
{
    if(m_buffer_size>0) {
        delete[] m_buffer;
    }
    m_buffer_size = size;
    m_buffer = new Sound::Sample[size];
    m_loop_length = size;
}

void Sound::insert_sample( const Sound::Sample& value )
{
    if(m_buffer_size>0) {
        if(m_write_pointer >= m_buffer_size) {
            m_write_pointer = 0;
        }
        m_buffer[m_write_pointer] = value;
        m_write_pointer++;
        m_loop_length = qMax(static_cast<double>(m_write_pointer),m_loop_length);
    }
}

const Sound::Sample& Sound::get_next_sample()
{
    // phase value (float) to buffer address (int)
    int m_read_pointer_int = static_cast<int>(m_read_pointer);

    // increase phase value
    m_read_pointer += m_read_speed;
    if(m_read_pointer > m_buffer_size) {
        m_read_pointer = m_start_point;
    }

    // return buffer value
    return m_buffer[m_read_pointer_int];
}

void Sound::set_read_speed(double s)
{
    qDebug() << "SoundSample::set_read_speed " << s;
    m_read_speed = s;
}

void Sound::setLoopLength(double l)
{
    if(l+m_start_point > m_buffer_size) {
        m_loop_length = m_buffer_size - m_start_point;
    } else {
        m_loop_length = l;
    }
}

void Sound::set_start_point(double p)
{
    if(p+m_loop_length > m_buffer_size) {
        m_start_point = m_buffer_size - m_loop_length;
    } else {
        m_start_point = p;
    }
}

int Sound::get_size()
{
    return m_buffer_size;
}

Sound::Sample Sound::get_sample_at(int i)
{
    Sound::Sample value;
    if(i<m_buffer_size) {
        value = m_buffer[i];
    }
    return value;
}

int Sound::get_write_pointer()
{
    return m_write_pointer;
}

int Sound::get_read_pointer()
{
    return m_read_pointer;
}

void Sound::normalize()
{
    double max_peak_left = 0;
    double max_peak_right = 0;
    for(int i=0;i<m_buffer_size;i++) {
        max_peak_left = qMax(max_peak_left,qAbs(m_buffer[i].left));
        max_peak_right = qMax(max_peak_right,qAbs(m_buffer[i].right));
    }
    double normalize_factor_left = 1 / max_peak_left;
    double normalize_factor_right = 1 / max_peak_right;
    for(int i=0;i<m_buffer_size;i++) {
        m_buffer[i].left = m_buffer[i].left * normalize_factor_left;
        m_buffer[i].right = m_buffer[i].right * normalize_factor_right;
    }
}
