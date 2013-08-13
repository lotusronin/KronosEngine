#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include "Texture.h"
#include <GL/glu.h>
#include <GL/gl.h>

class ResourceManager {
protected:
//thinking of vectors for images, music, and sound effects here
std::vector<Texture*> tvec;
public:
    ResourceManager();
    ~ResourceManager();
    void loadTexture();
    GLuint getTexture();
    void loadMusic();
    void getMusic();
    void loadSFX();
    void getSFX();
};


#endif
