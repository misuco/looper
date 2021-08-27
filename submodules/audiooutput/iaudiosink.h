#ifndef IAUDIOSINK_H
#define IAUDIOSINK_H

#include <submodules/soundsample/sound.h>

class IAudioSink
{
public:
    virtual ~IAudioSink() {}
    virtual void insert_sample( const Sound::Sample& ) = 0;
};

#endif // IAUDIOSINK_H
