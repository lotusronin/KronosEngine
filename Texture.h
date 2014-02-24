#ifndef TEXTURE_H
#define TEXTURE_H
#include <FreeImage.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Texture{
protected:
    GLuint t;
public:
    Texture();
    GLuint getTexture();
};

#endif // TEXTURE_H