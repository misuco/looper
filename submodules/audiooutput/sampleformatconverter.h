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
