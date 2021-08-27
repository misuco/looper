#include "sampleformatconverter.h"
#include <QtEndian>
#include <QDebug>
#include <qquickitem.h>

SampleFormatConverter::SampleFormatConverter(const QAudioFormat &format,
                     QObject *parent)
    :   QIODevice(parent)
    ,   m_audio_source{nullptr}
    ,   m_audio_sink{nullptr}
    ,   m_format(format)
    ,   m_maxAmplitude(0)
    ,   m_sample_rate(format.sampleRate())
    ,   m_latest_samples_left(new Sample_graph_model)
    ,   m_latest_samples_right(new Sample_graph_model)
{
    switch (m_format.sampleSize()) {
    case 8:
        m_maxAmplitude = 127;
        break;
    case 16:
        m_maxAmplitude = 32767;
        break;

    case 32:
        m_maxAmplitude = 0x7fffffff;
        break;

    default:
        break;
    }
}

SampleFormatConverter::~SampleFormatConverter()
{
}

void SampleFormatConverter::start()
{
    open(QIODevice::ReadOnly);
}

void SampleFormatConverter::stop()
{
    close();
}

qint64 SampleFormatConverter::readData(char *data, qint64 len)
{
    Q_ASSERT(m_format.sampleSize() % 8 == 0);
    const int channelBytes = m_format.sampleSize() / 8;
    const int sampleBytes = m_format.channelCount() * channelBytes;
    Q_ASSERT(len % sampleBytes == 0);
    const int numSamples = len / sampleBytes;

    unsigned char *ptr = reinterpret_cast<unsigned char *>(data);

    for (int i = 0; i < numSamples; ++i) {
        Sound::Sample sample;
        if(m_audio_source) {
            sample = m_audio_source->get_next_sample();
        }
        for (int j = 0; j < 2; j++) {
            double next_sample;
            if(j==0) next_sample = sample.left;
            else next_sample = sample.right;

            if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                quint8 value = m_maxAmplitude + next_sample * m_maxAmplitude;
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::SignedInt) {
                qint8 value = next_sample * m_maxAmplitude;
                *reinterpret_cast<qint8*>(ptr) = value;
            } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                quint16 value = m_maxAmplitude + next_sample * m_maxAmplitude;
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    *reinterpret_cast<quint16*>(ptr) = qToLittleEndian<quint16>(value);
                else
                    *reinterpret_cast<quint16*>(ptr) = qToBigEndian<quint16>(value);
            } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::SignedInt) {
                qint16 value = next_sample * m_maxAmplitude;
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    *reinterpret_cast<qint16*>(ptr) = qToLittleEndian<qint16>(value);
                else
                    *reinterpret_cast<qint16*>(ptr) = qToBigEndian<qint16>(value);
            } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                quint32 value = m_maxAmplitude + next_sample * m_maxAmplitude;
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    *reinterpret_cast<quint32*>(ptr) = qToLittleEndian<quint32>(value);
                else
                    *reinterpret_cast<quint32*>(ptr) = qToBigEndian<quint32>(value);
            } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::SignedInt) {
                qint32 value = next_sample * m_maxAmplitude;
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    *reinterpret_cast<qint32*>(ptr) = qToLittleEndian<qint32>(value);
                else
                    *reinterpret_cast<qint32*>(ptr) = qToBigEndian<qint32>(value);
            } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::Float) {
                *reinterpret_cast<float*>(ptr) = next_sample; // assumes 0-1.0
            }

            ptr += channelBytes;
        }
    }

    return len;
}

qint64 SampleFormatConverter::writeData(const char *data, qint64 len)
{
    //qDebug() << "SampleMemory::writeData " << len;

    Q_ASSERT(m_format.sampleSize() % 8 == 0);
    const int channelBytes = m_format.sampleSize() / 8;
    const int sampleBytes = m_format.channelCount() * channelBytes;
    Q_ASSERT(len % sampleBytes == 0);
    const int numSamples = len / sampleBytes;

    //quint32 maxValue = 0;
    const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);

    m_peak = 0;

    for (int i = 0; i < numSamples; ++i) {
        Sound::Sample sample;
        for (int j = 0; j < m_format.channelCount(); ++j) {
            double value = 0;

            if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                value = (*reinterpret_cast<const quint8*>(ptr) - m_maxAmplitude) / m_maxAmplitude;
            } else if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::SignedInt) {
                value = *reinterpret_cast<const qint8*>(ptr) / m_maxAmplitude;
            } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    value = (qFromLittleEndian<quint16>(ptr) - m_maxAmplitude) / m_maxAmplitude;
                else
                    value = (qFromBigEndian<quint16>(ptr)- m_maxAmplitude) / m_maxAmplitude;
            } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::SignedInt) {
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    value = qFromLittleEndian<qint16>(ptr) / m_maxAmplitude;
                else
                    value = qFromBigEndian<qint16>(ptr) / m_maxAmplitude;
            } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    value = (qFromLittleEndian<quint32>(ptr)  - m_maxAmplitude) / m_maxAmplitude;
                else
                    value = (qFromBigEndian<quint32>(ptr)  - m_maxAmplitude ) / m_maxAmplitude;
            } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::SignedInt) {
                if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                    value = qFromLittleEndian<qint32>(ptr) / m_maxAmplitude;
                else
                    value = qFromBigEndian<qint32>(ptr) / m_maxAmplitude;
            } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::Float) {
                value = *reinterpret_cast<const float*>(ptr); // assumes 0-1.0
            }

            if( j == 0 ) sample.left = value;
            else if( j == 1 ) sample.right = value;

            m_peak = qMax(m_peak,qAbs(value));

            if(j==0) {
                if(i<400) {
                    if(m_latest_samples_left->size()<=i) {
                        m_latest_samples_left->append(value);
                    } else {
                        m_latest_samples_left->replace(i,value);
                    }
                }
            } else {
                if(i<400) {
                    if(m_latest_samples_right->size()<=i) {
                        m_latest_samples_right->append(value);
                    } else {
                        m_latest_samples_right->replace(i,value);
                    }
                }
            }

            ptr += channelBytes;
        }

        if(m_audio_sink) {
            m_audio_sink->insert_sample( sample );
        }

    }

    m_latest_samples_left->update();
    emit QmlPeakUpdated();

    return len;
}

qint64 SampleFormatConverter::bytesAvailable() const
{
    return 4096;
}

void SampleFormatConverter::set_sink(IAudioSink *s)
{
    m_audio_sink = s;
}

void SampleFormatConverter::set_source(IAudioSource *s)
{
    m_audio_source = s;
}

