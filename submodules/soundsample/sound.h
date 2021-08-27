#ifndef SOUND_H
#define SOUND_H


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

private:
    int m_buffer_size;
    Sample * m_buffer;
    int m_write_pointer;
    double m_read_pointer;
    double m_read_speed;
    double m_previous_sample;
    double m_loop_length;
    double m_start_point;

};

#endif // SOUND_H
