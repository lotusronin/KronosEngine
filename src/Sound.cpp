#include "Sound.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>


Sound::Sound(std::string fname, bool _error, ALenum _fmt, ALvoid* _data, ALsizei _sz, ALsizei _freq) : listenerOri {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}
{
    name = fname;
    loop = AL_FALSE;
    Error = _error;
    

    if(!Error)
    {
        //Set up our listener
        alListener3f(AL_POSITION, 0, 0, 1.0f);
        alListener3f(AL_VELOCITY, 0, 0, 0);
        alListenerfv(AL_ORIENTATION, listenerOri);

        //Set up our source
        alGenSources((ALuint)1, &source);

        alSourcef(source, AL_PITCH, 1);
        alSourcef(source, AL_GAIN, 1);
        alSource3f(source, AL_POSITION, 0, 0, 0);
        alSource3f(source, AL_VELOCITY, 0, 0, 0);
        alSourcei(source, AL_LOOPING, AL_FALSE);

        //generate sound buffer
        alGenBuffers((ALuint)1, &buffer);

        //load sound file
        format = _fmt;
        data = _data;
        sz = _sz;
        freq = _freq;
        alBufferData(buffer, format, data, sz, freq);

        //Bind source
        alSourcei(source, AL_BUFFER, buffer);
    }
}

Sound::~Sound()
{
    alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}

void Sound::Play()
{
    if(!Error)
        alSourcePlay(source);
}

bool Sound::isPlaying()
{
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    return (source_state == AL_PLAYING);
}

std::string Sound::getName()
{
    return name;
}
