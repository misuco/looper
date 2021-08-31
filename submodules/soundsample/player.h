/**
 *
 * Copyright (C) 2021 Claudio Zopfi
 *
 * This file is part of the Looper project ( https://github.com/misuco/looper )
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
