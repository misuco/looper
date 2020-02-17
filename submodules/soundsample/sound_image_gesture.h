#ifndef SOUND_IMAGE_GESTURE_H
#define SOUND_IMAGE_GESTURE_H

#include <QObject>
#include <QMap>
#include "player.h"
#include "soundsample.h"

class Sound_image_gesture : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void set_width(double w);
    Q_INVOKABLE void set_height(double h);

    Q_INVOKABLE void pressed(QVariant x);
    Q_INVOKABLE void updated(QVariant x);
    Q_INVOKABLE void released(QVariant x);
    Q_INVOKABLE void canceled(QVariant x);

    explicit Sound_image_gesture(Player * p, QObject *parent = nullptr);

    void set_sample(SoundSample *s, int channel);

private:
    Player * m_player;
    static const int s_channel_count = 2;
    SoundSample * m_sound_samples[s_channel_count];

    // indexes of metaproperties
    const int c_point_id_index = 1;
    const int c_x_index = 4;
    const int c_y_index = 5;
    struct TouchPoint {
        double x;
        double y;
    };

    double m_width;
    double m_height;

    QMap<int,TouchPoint> m_touched;
    int m_touch_count;

    void calculate();

};

#endif // SOUND_IMAGE_GESTURE_H
