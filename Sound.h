#ifndef SOUND_H
#define SOUND_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>

class Sound{
protected:
    ALCdevice* device;
	ALCcontext* context;
	ALfloat listenerOri[6];
	ALuint source, buffer;
	ALint source_state;

	ALboolean loop;
	ALsizei sz, freq;
	ALenum format;
	ALvoid* data;

	bool Error;
	std::string name;
public:
    Sound(std::string fname);
    ~Sound();
    void Play();
    void Pause();
    bool isPlaying();
    void setLoop(bool l);
};

#endif
