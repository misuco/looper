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

#ifndef SOUND_H
#define SOUND_H

#include <QString>

class Sound
{
public:
    Sound();
    ~Sound();

    struct Sample {
        double left;
        double right;
    };

    void init(int size);

    void insert_sample(const Sample &value);
    const Sample& get_next_sample();
    void set_read_speed(double s);
    void setLoopLength(double l);
    void set_start_point(double p);

    int get_size();
    Sample get_sample_at(int i);

    int get_write_pointer();
    int get_read_pointer();

    void normalize();

    bool init_from_file(QString filename);

private:
    int m_buffer_size;
    Sample * m_buffer;
    int m_write_pointer;
    double m_read_pointer;
    double m_read_speed;
    //double m_previous_sample;
    double m_loop_length;
    double m_start_point;

};

#endif // SOUND_H
