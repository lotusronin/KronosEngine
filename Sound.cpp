#include "Sound.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>

Sound::Sound(std::string fname) : listenerOri {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}
{
    loop = AL_FALSE;
    Error = false;

	device = alcOpenDevice(NULL);
	if(!device)
	{
		std::cout << "Error opening sound device!!!\n";
		Error = true;
	}

	context = alcCreateContext(device, NULL);

	if(!alcMakeContextCurrent(context))
	{
		std::cout << "Error setting up context!!!\n";
		Error = true;
	}


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
        alutLoadWAVFile((ALbyte *)fname.c_str(), &format, &data, &sz, &freq, &loop);

        alBufferData(buffer, format, data, sz, freq);

        //Bind source
        alSourcei(source, AL_BUFFER, buffer);
    }
}

Sound::~Sound()
{
    alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
	std::cout << "OpenAL all cleaned up!\n";
}

void Sound::Play()
{
    if(!Error)
        alSourcePlay(source);
}

bool Sound::isPlaying()
{
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    if(source_state == AL_PLAYING)
    {
        return true;
    }
    else
        return false;
}
