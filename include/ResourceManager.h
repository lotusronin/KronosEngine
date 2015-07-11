#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include "Texture.h"
#include "Sound.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <vorbis/vorbisfile.h>

class ResourceManager {
protected:
//thinking of vectors for images, music, and sound effects here
std::vector<Texture*> tvec;
std::vector<Sound*> svec;
float backup[2];
public:
    ResourceManager();
    ~ResourceManager();
    void loadTexture(const std::string& texname);
    GLuint getTexture(const std::string& texname);
    float* getTextureFrames(const std::string& texname);
    void incrementFrame();
    void initSound();
    void loadMusic(const std::string& musname);
    void getMusic();
    void loadSFX();
    void getSFX();
    void loadOgg(const std::string& filename);
private:
    //OpenAL specific
    ALCdevice* m_device;
    ALCcontext* m_context;
    bool m_alError;
};


#endif
