/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <qmath.h>
#include <qendian.h>

#include "audiooutput.h"

AudioOutputController::AudioOutputController(QObject * parent)
    :   QObject(parent)
    ,   m_sample_rate(44100)
    ,   m_OutputBufferSize(4096)
    ,   m_pushTimer(new QTimer(this))
    ,   m_device(QAudioDeviceInfo::defaultOutputDevice())
    ,   m_sample_memory(nullptr)
    ,   m_audioOutput(nullptr)
    ,   m_output(nullptr)
    ,   m_pullMode(true)
    ,   m_buffer(m_OutputBufferSize, 0)
{
    initializeAudio();
}

void AudioOutputController::initializeAudio()
{
    connect(m_pushTimer, SIGNAL(timeout()), SLOT(pushTimerExpired()));

    m_format.setSampleRate(m_sample_rate);
    m_format.setChannelCount(2);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(m_device);
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }    

}

void AudioOutputController::set_source(SampleFormatConverter * sampleMemory) {
    m_sample_memory = sampleMemory;
}


void AudioOutputController::create_audio_output()
{
    delete m_audioOutput;
    m_audioOutput = nullptr;
    m_audioOutput = new QAudioOutput(m_device, m_format, this);
    //m_audioOutput->setBufferSize(m_OutputBufferSize);

    m_sample_memory->start();
    m_audioOutput->start(m_sample_memory);

    qreal initialVolume = QAudio::convertVolume(m_audioOutput->volume(),
                                                QAudio::LinearVolumeScale,
                                                QAudio::LogarithmicVolumeScale);
}

QAudioFormat &AudioOutputController::getAudioFormat()
{
    return m_format;
}

AudioOutputController::~AudioOutputController()
{

}

void AudioOutputController::deviceChanged(int index)
{
    m_pushTimer->stop();
    m_sample_memory->stop();
    m_audioOutput->stop();
    m_audioOutput->disconnect(this);
    initializeAudio();
}

void AudioOutputController::volumeChanged(int value)
{
    if (m_audioOutput) {
        qreal linearVolume =  QAudio::convertVolume(value / qreal(100),
                                                    QAudio::LogarithmicVolumeScale,
                                                    QAudio::LinearVolumeScale);

        m_audioOutput->setVolume(linearVolume);
    }
}

void AudioOutputController::pushTimerExpired()
{
    if (m_audioOutput && m_audioOutput->state() != QAudio::StoppedState) {
        int chunks = m_audioOutput->bytesFree()/m_audioOutput->periodSize();
        while (chunks) {
           const qint64 len = m_sample_memory->read(m_buffer.data(), m_audioOutput->periodSize());
           if (len)
               m_output->write(m_buffer.data(), len);
           if (len != m_audioOutput->periodSize())
               break;
           --chunks;
        }
    }
}

void AudioOutputController::toggleMode()
{
    m_pushTimer->stop();
    m_audioOutput->stop();

    if (m_pullMode) {
        //switch to push mode (periodically push to QAudioOutput using a timer)
        m_output = m_audioOutput->start();
        m_pullMode = false;
        m_pushTimer->start(20);
    } else {
        //switch to pull mode (QAudioOutput pulls from Generator as needed)
        m_pullMode = true;
        m_audioOutput->start(m_sample_memory);
    }

}

void AudioOutputController::toggleSuspendResume()
{
    if (m_audioOutput->state() == QAudio::SuspendedState) {
        m_audioOutput->resume();
    } else if (m_audioOutput->state() == QAudio::ActiveState) {
        m_audioOutput->suspend();
    } else if (m_audioOutput->state() == QAudio::StoppedState) {
        m_audioOutput->resume();
    } else if (m_audioOutput->state() == QAudio::IdleState) {
        // no-op
    }
}

