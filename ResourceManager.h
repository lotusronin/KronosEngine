#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include "Texture.h"
#include "Sound.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

class ResourceManager {
protected:
//thinking of vectors for images, music, and sound effects here
std::vector<Texture*> tvec;
std::vector<Sound*> svec;
public:
    ResourceManager();
    ~ResourceManager();
    void loadTexture(std::string texname);
    GLuint getTexture();
    void loadMusic(std::string musname);
    void getMusic();
    void loadSFX();
    void getSFX();
};


#endif
