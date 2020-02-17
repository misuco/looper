#ifndef SAMPLEMEMORY_H
#define SAMPLEMEMORY_H

#include <QObject>
#include <QByteArray>
#include <QIODevice>
#include <QAudioFormat>
#include <QVariant>
#include <QDebug>

#include "submodules/soundsample/sample_graph_model.h"
#include "iaudiosource.h"
#include "iaudiosink.h"

class SampleFormatConverter : public QIODevice
{
    Q_OBJECT

    Q_PROPERTY(Sample_graph_model* latest MEMBER m_latest_samples_left NOTIFY QmlLatesSamplesUpdated)
    Q_PROPERTY(double peak MEMBER m_peak NOTIFY QmlPeakUpdated)

public:

    SampleFormatConverter(const QAudioFormat &format, QObject *parent = nullptr);
    ~SampleFormatConverter() override;

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

    void set_sink(IAudioSink * s);
    void set_source(IAudioSource * s);

signals:
    void QmlLatesSamplesUpdated();
    void QmlPeakUpdated();

private:
    IAudioSource * m_audio_source;
    IAudioSink * m_audio_sink;

    QAudioFormat m_format;
    double m_maxAmplitude;
    int m_sample_rate;

    Sample_graph_model* m_latest_samples_left;
    Sample_graph_model* m_latest_samples_right;
    double m_peak;

};

#endif // SAMPLEMEMORY_H
