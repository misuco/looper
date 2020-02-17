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

#include <stdlib.h>
#include <math.h>

#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QAudioInput>

#include "audioinput.h"

AudioInputController::AudioInputController(QObject *parent)
    :   QObject(parent)
    ,   m_device(QAudioDeviceInfo::defaultInputDevice())
    ,   m_audioInfo(nullptr)
    ,   m_audioInput(nullptr)
    ,   m_input(nullptr)
    ,   m_pullMode(true)
    ,   m_InputBufferSize(4096)
    ,   m_buffer(m_InputBufferSize, 0)
{
}

AudioInputController::~AudioInputController() {}

void AudioInputController::initialize_audio(QAudioFormat &format)
{
    m_format = format;

    if (m_audioInfo)
        delete m_audioInfo;
    m_audioInfo  = new AudioInfo(m_format, this);
    //connect(m_audioInfo, SIGNAL(update()), SLOT(refreshDisplay()));

}

void AudioInputController::create_audio_input()
{
    m_audioInput = new QAudioInput(m_device, m_format, this);
    //m_audioInput->setBufferSize(m_InputBufferSize);

    m_audioInfo->setSampleMemory(m_sample_memory);
    /*
    qreal initialVolume = QAudio::convertVolume(m_audioInput->volume(),
                                                QAudio::LinearVolumeScale,
                                                QAudio::LogarithmicVolumeScale);
                                                */
    m_audioInfo->start();
    m_audioInput->start(m_audioInfo);
}


void AudioInputController::set_sink(SampleFormatConverter * sampleMemory) {
    m_sample_memory = sampleMemory;
}


void AudioInputController::readMore()
{
    if (!m_audioInput)
        return;

    qint64 len = m_audioInput->bytesReady();
    char buffer[len];
    qint64 l = m_input->read(buffer, len);
    m_sample_memory->writeData(buffer,len);
    if (l > 0)
        m_audioInfo->write(m_buffer.constData(), l);

    /*
    qint64 len = m_audioInput->bytesReady();
    if (len > m_InputBufferSize)
        len = m_InputBufferSize;
    qint64 l = m_input->read(m_buffer.data(), len);
    if (l > 0)
        m_audioInfo->write(m_buffer.constData(), l);
    */
}

void AudioInputController::toggleMode()
{
    // Change bewteen pull and push modes
    m_audioInput->stop();

    if (m_pullMode) {
        m_input = m_audioInput->start();
        connect(m_input, SIGNAL(readyRead()), SLOT(readMore()));
        m_pullMode = false;
    } else {
        m_pullMode = true;
        m_audioInput->start(m_audioInfo);
    }

}

void AudioInputController::toggleSuspend()
{
    // toggle suspend/resume
    if (m_audioInput->state() == QAudio::SuspendedState) {
        m_audioInput->resume();
    } else if (m_audioInput->state() == QAudio::ActiveState) {
        m_audioInput->suspend();
    } else if (m_audioInput->state() == QAudio::StoppedState) {
        m_audioInput->resume();
    } else if (m_audioInput->state() == QAudio::IdleState) {
        // no-op
    }
}

/*
void AudioInputController::refreshDisplay()
{
    //m_canvas->setLevel(m_audioInfo->level());
}
*/

void AudioInputController::deviceChanged(int index)
{
    m_audioInfo->stop();
    m_audioInput->stop();
    m_audioInput->disconnect(this);
    delete m_audioInput;

    initialize_audio(m_format);
}

void AudioInputController::setVolume(int value)
{
    if (m_audioInput) {
        qreal linearVolume =  QAudio::convertVolume(value / qreal(100),
                                                    QAudio::LogarithmicVolumeScale,
                                                    QAudio::LinearVolumeScale);

        m_audioInput->setVolume(linearVolume);
    }
}
