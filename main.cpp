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
    //sample.init(88200);
    //sample.init_from_file( "qrc:/res/wav/t1.wav");

    Recorder recorder;
    recorder.set_sample(&sample);

    Player player;
    player.set_sample(&sample);

    Sound_image sound_image;
    sound_image.set_width(400);
    sound_image.set_sample(&sample);

    Sound_image_gesture sound_image_gesture(&player);
    sound_image_gesture.set_sample(&sample);

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
    ctx->setContextProperty("sound_image", &sound_image);
    ctx->setContextProperty("sound_image_gesture", &sound_image_gesture);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
