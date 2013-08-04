#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/* Various #include statements to go here for needed libs... currently thinking of FreeImage, wolfire uses it... */
#include <vector>

class ResourceManager {
protected:
//thinking of vectors for images, music, and sound effects here
public:
    ResourceManager();
    ~ResourceManager();
    void loadTexture();
    void getTexture();
    void loadMusic();
    void getMusic();
    void loadSFX();
    void getSFX();
};


#endif
