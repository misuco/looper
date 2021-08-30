#include "track.h"
#include <QDebug>

void Track::click( double x, double y)
{
    qDebug() << "click x:" << x << " y:" << y;
    m_muted = !m_muted;
    emit QmlMutedUpdated();
}

Track::Track(QString name, QObject *parent) : QObject(parent)
{
    m_name = name;
    m_muted = false;
}

void Track::set_play_pos(double p)
{
    m_play_pos = p;
    emit QmlPlayPosUpdated();
}

bool Track::get_muted()
{
    return m_muted;
}
