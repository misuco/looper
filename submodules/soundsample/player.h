#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVariant>

#include "sound.h"
#include "submodules/audiooutput/iaudiosource.h"

class Player : public QObject, public IAudioSource
{
    Q_OBJECT

    Q_PROPERTY(int  play_pos    MEMBER m_play_pos    NOTIFY QmlPlayPosUpdated)

public:
    explicit Player(QObject *parent = nullptr);

    virtual const Sound::Sample &get_next_sample();
    void set_sample(Sound * s);
    void set_playing(bool state);

signals:
    void QmlPlayPosUpdated();

public slots:

private:
    Sound * m_sound_sample;

    bool m_playing;
    int  m_play_pos;

    void calculate();
};

#endif // PLAYER_H
