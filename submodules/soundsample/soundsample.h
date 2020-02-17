#ifndef SOUNDSAMPLE_H
#define SOUNDSAMPLE_H


class SoundSample
{
public:
    SoundSample();
    ~SoundSample();

    void init(int size);

    void insert_sample(double value);
    double get_next_sample();
    void set_read_speed(double s);
    void setLoopLength(double l);
    void set_start_point(double p);

    int get_size();
    double get_sample_at(int i);

    void normalize();

private:
    int m_buffer_size;
    double * m_buffer;
    int m_write_pointer;
    double m_read_pointer;
    double m_read_speed;
    double m_previous_sample;
    double m_loop_length;
    double m_start_point;

};

#endif // SOUNDSAMPLE_H
