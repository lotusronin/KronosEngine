#ifndef TEXTURE_H
#define TEXTURE_H
#include <FreeImage.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

class Texture{
protected:
    GLuint t;
    std::string name;
public:
    Texture(std::string texname);
    GLuint getTexture();
    std::string getName();
};

#endif // TEXTURE_H
