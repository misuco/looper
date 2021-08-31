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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "submodules/audioinput/audioinput.h"
#include "submodules/audiooutput/audiooutput.h"
#include "submodules/soundsample/player.h"
#include "submodules/soundsample/recorder.h"
#include "submodules/soundsample/sound.h"
#include "submodules/soundsample/sound_image.h"
#include "submodules/soundsample/sound_image_gesture.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("misuco");
    app.setOrganizationDomain("misuco.org");

    AudioInputController audio_input_controller;
    AudioOutputController audio_output_controller;

    Sound sample;

    Recorder recorder;
    recorder.set_sample(&sample);

    Player player;
    player.set_sample(&sample);

    /*
    Sound_image sound_image;
    sound_image.set_width(400);
    sound_image.set_sample(&sample);

    Sound_image_gesture sound_image_gesture(&player);
    sound_image_gesture.set_sample(&sample);
    */

    SampleFormatConverter sample_format_converter(audio_output_controller.getAudioFormat());

    sample_format_converter.set_sink(&recorder);
    sample_format_converter.set_source(&player);

    audio_input_controller.set_sink(&sample_format_converter);
    audio_input_controller.initialize_audio(audio_output_controller.getAudioFormat());
    audio_input_controller.create_audio_input();

    audio_output_controller.set_source(&sample_format_converter);
    audio_output_controller.create_audio_output();

    QQmlApplicationEngine engine;
    qmlRegisterType<Sample_graph_model>("com.c1audio", 1, 0, "SampleGraphModel");

    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("samples", &sample_format_converter);
    ctx->setContextProperty("player", &player);
    ctx->setContextProperty("recorder", &recorder);
//    ctx->setContextProperty("sound_image", &sound_image);
//    ctx->setContextProperty("sound_image_gesture", &sound_image_gesture);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
