#include "track.h"

Track::Track(QString name, QObject *parent) : QObject(parent)
{
    m_name = name;
}

void Track::set_play_pos(double p)
{
    m_play_pos = p;
    emit QmlPlayPosUpdated();
}
