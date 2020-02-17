#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QIODevice>
#include <QAudioFormat>
#include "submodules/audiooutput/sampleformatconverter.h"

class AudioInfo : public QIODevice
{
    Q_OBJECT

public:
    AudioInfo(const QAudioFormat &format, QObject *parent);
    ~AudioInfo();

    void setSampleMemory(SampleFormatConverter *sampleMemory);

    void start();
    void stop();

    qreal level() const { return m_level; }

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    const QAudioFormat m_format;
    qreal m_level; // 0.0 <= m_level <= 1.0
    SampleFormatConverter *m_sample_memory;

signals:
    void update();
};


#endif // AUDIOINFO_H
