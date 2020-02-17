#ifndef IAUDIOSINK_H
#define IAUDIOSINK_H

class IAudioSink
{
public:
    virtual ~IAudioSink() {}
    virtual void insert_sample(double value, int channel) = 0;
};

#endif // IAUDIOSINK_H
