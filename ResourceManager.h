#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/* Various #include statements to go here for needed libs... currently thinking of FreeImage, wolfire uses it... */
#include <vector>
#include <FreeImage.h>
#include "Texture.h"

class ResourceManager {
protected:
//thinking of vectors for images, music, and sound effects here
std::vector<Texture*> textures_vec;
public:
    ResourceManager();
    ~ResourceManager();
    void loadTexture();
    FIBITMAP* getTexture();
    void loadMusic();
    void getMusic();
    void loadSFX();
    void getSFX();
};


#endif
