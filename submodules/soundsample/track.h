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

#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString  name    MEMBER m_name     NOTIFY QmlNameUpdated)
    Q_PROPERTY(double  play_pos MEMBER m_play_pos NOTIFY QmlPlayPosUpdated)
    Q_PROPERTY(bool    muted    MEMBER m_muted    NOTIFY QmlMutedUpdated)

public:
    Q_INVOKABLE void click(double x, double y);

    explicit Track(QObject *parent = nullptr);
    Track(QString name, QObject *parent = nullptr);

    void set_play_pos( double p );
    bool get_muted();

signals:
    void QmlNameUpdated();
    void QmlPlayPosUpdated();
    void QmlMutedUpdated();

private:
    QString m_name;
    double m_play_pos;
    int m_length;
    bool m_muted;

};

#endif // TRACK_H
