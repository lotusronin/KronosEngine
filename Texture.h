#ifndef TEXTURE_H
#define TEXTURE_H
#include <FreeImage.h>

class Texture{
protected:
    FIBITMAP* texture;
public:
    Texture();
    FIBITMAP* getTexture();
};

#endif // TEXTURE_H
