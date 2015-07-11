#include "Texture.h"
#include <FreeImage.h>
#include <iostream>
#include <stdlib.h>
#include <string>

Texture::Texture(const std::string& texname)
{
    name = texname;
    frame = 1;
    glGenTextures( 1, &t );
    if(isdigit(name[0]) && name.find("antex") != std::string::npos) {
        frameInfo[0] = 1.0f;
        char temp = name[0];
        frameInfo[1] = atof(&temp);
    } else {
        frameInfo[0] = 1.0f;
        frameInfo[1] = 1.0f;
    }

}

Texture::~Texture()
{
    glDeleteTextures(1, &t);
}

GLuint Texture::getTexture()
{
    return t;
}

std::string Texture::getName()
{
    return name;
}

void Texture::FITexture(int imgWidth, int imgHeight, FIBITMAP* texture)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, t );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(texture));

    //std::cout << "Image file is good\n";
    std::cout << "Loaded: " << name << "\n";
}

void Texture::FontTexture(int imgWidth, int imgHeight, unsigned char* texture)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, t );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, imgWidth, imgHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, texture);
    //std::cout << "Font texture for '" << name << "' made!\n";
}

void Texture::incrementFrame() {
    frame++;

    if(60/frameInfo[1] < float(frame)) {
        if(frameInfo[1] == frameInfo[0]) {
            frameInfo[0] = 1.0f;
        } else {
            frameInfo[0]++;
        }
        frame = 1;
    }
}

float* Texture::getFrameInfo() {
    return frameInfo;
}

