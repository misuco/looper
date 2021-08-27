#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include "submodules/audiooutput/iaudiosink.h"
#include "sound.h"

class Recorder : public QObject, public IAudioSink
{
    Q_OBJECT

    Q_PROPERTY(bool record_enable MEMBER m_record_enable NOTIFY QmlRecordEnabledUpdated)
    Q_PROPERTY(int  record_pos    MEMBER m_record_pos    NOTIFY QmlRecordPosUpdated)

public:
    Q_INVOKABLE void record(bool enable);

    explicit Recorder(QObject *parent = nullptr);
    virtual void insert_sample( const Sound::Sample& s );
    void set_sample(Sound * s);

signals:
    void QmlRecordEnabledUpdated();
    void QmlRecordPosUpdated();

private:
    Sound * m_sound_sample;

    bool m_record_enable;
    int  m_record_pos;

};

#endif // RECORDER_H
