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
    Texture(const std::string& texname);
    GLuint getTexture();
    std::string getName();
    void FITexture(int imgWidth, int imgHeight, FIBITMAP* texture);
    void FontTexture(int imgWidth, int imgHeight, unsigned char* texture);
};

#endif // TEXTURE_H
