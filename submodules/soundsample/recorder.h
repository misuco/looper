#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include "submodules/audiooutput/iaudiosink.h"
#include "soundsample.h"

class Recorder : public QObject, public IAudioSink
{
    Q_OBJECT

    Q_PROPERTY(bool record_enable MEMBER m_record_enable NOTIFY QmlRecordEnabledUpdated)

public:
    Q_INVOKABLE void record(bool enable);

    explicit Recorder(QObject *parent = nullptr);
    virtual void insert_sample(double value, int channel);
    void set_sample(SoundSample * s, int channel);

signals:
    void QmlRecordEnabledUpdated();

private:
    static const int s_channel_count = 2;
    SoundSample * m_sound_samples[s_channel_count];

    bool m_record_enable;

};

#endif // RECORDER_H
