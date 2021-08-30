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
    Q_PROPERTY(bool playing     MEMBER m_playing     NOTIFY QmlPlayingUpdated)
    Q_PROPERTY(QList<QObject *> tracks MEMBER m_tracks NOTIFY QmlTracksUpdated)

public:
    Q_INVOKABLE void factory_preset();
    Q_INVOKABLE void load_sample( QString filename );
    Q_INVOKABLE void set_playing(bool state);

    explicit Player(QObject *parent = nullptr);

    virtual const Sound::Sample &get_next_sample();
    void set_sample(Sound * s);

signals:
    void QmlPlayPosUpdated();
    void QmlPlayingUpdated();
    void QmlTracksUpdated();

public slots:

private:
    Sound * m_sound_sample;
    QList<Sound *> m_sound_samples;
    QList<QObject *> m_tracks;

    const Sound::Sample m_silence;

    bool m_playing;
    int  m_play_pos;

    int m_update_counter;

    Sound::Sample m_next_sample;

    void calculate();
};

#endif // PLAYER_H
