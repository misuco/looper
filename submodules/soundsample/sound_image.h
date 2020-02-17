#ifndef SOUND_IMAGE_H
#define SOUND_IMAGE_H

#include <QObject>
#include "sample_graph_model.h"
#include "soundsample.h"

class Sound_image : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Sample_graph_model* graph MEMBER m_graph NOTIFY qml_image_updated)

public:
    Q_INVOKABLE void set_width(double w);
    Q_INVOKABLE void calculate_graph();

    explicit Sound_image(QObject *parent = nullptr);
    void set_sample(SoundSample * s);

signals:
    void qml_image_updated();

private:
    Sample_graph_model* m_graph;
    SoundSample* m_sample;
    double m_width;

};

#endif // SOUND_IMAGE_H
