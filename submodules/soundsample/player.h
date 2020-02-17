#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVariant>

#include "soundsample.h"
#include "submodules/audiooutput/iaudiosource.h"

class Player : public QObject, public IAudioSource
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    virtual double get_next_sample(int channel);

    void set_sample(SoundSample * s, int channel);

    void set_playing(bool state);

signals:

public slots:

private:
    static const int s_channel_count = 2;
    SoundSample * m_sound_samples[s_channel_count];

    bool m_playing;

    void calculate();
};

#endif // PLAYER_H
