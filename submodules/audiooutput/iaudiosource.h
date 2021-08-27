#ifndef IAUDIOSOURCE_H
#define IAUDIOSOURCE_H

#include <submodules/soundsample/sound.h>

class IAudioSource
{
public:
    virtual ~IAudioSource() {}
    virtual const Sound::Sample& get_next_sample() = 0;
};

#endif // IAUDIOSOURCE_H
