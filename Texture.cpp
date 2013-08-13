#include "Texture.h"
#include <FreeImage.h>
#include <iostream>
#include <stdlib.h>

Texture::Texture(){
    FIBITMAP* texture;
    FREE_IMAGE_FORMAT fif;

    fif = FreeImage_GetFileType("res/tex_ground.xpm",0);
    if( FreeImage_FIFSupportsReading(fif))
    {
        texture = FreeImage_Load(fif, "res/tex_ground.xpm");
        int imgWidth = FreeImage_GetWidth(texture);
        int imgHeight = FreeImage_GetHeight(texture);
        //std::cout << imgWidth << " "<< imgHeight <<"\n";

        glGenTextures( 1, &t );
        glBindTexture( GL_TEXTURE_2D, t );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(texture));
        FreeImage_Unload(texture);
        std::cout << "File is good\n";
    }
    else
    {
        std::cout << "File not supported!\n";
    }
}

GLuint Texture::getTexture(){
    return t;
}
