#ifndef IAUDIOSOURCE_H
#define IAUDIOSOURCE_H

class IAudioSource
{
public:
    virtual ~IAudioSource() {}
    virtual double get_next_sample(int channel) = 0;
};

#endif // IAUDIOSOURCE_H
