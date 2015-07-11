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
    float frameInfo[2];
    int frame;
public:
    Texture(const std::string& texname);
    ~Texture();
    GLuint getTexture();
    std::string getName();
    void FITexture(int imgWidth, int imgHeight, FIBITMAP* texture);
    void FontTexture(int imgWidth, int imgHeight, unsigned char* texture);
    void incrementFrame();
    float* getFrameInfo();
};

#endif // TEXTURE_H
