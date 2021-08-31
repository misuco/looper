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
