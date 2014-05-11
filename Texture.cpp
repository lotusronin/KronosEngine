#include "Texture.h"
#include <FreeImage.h>
#include <iostream>
#include <stdlib.h>
#include <string>

Texture::Texture(const std::string& texname){
    name = texname;
    FIBITMAP* texture;
    FREE_IMAGE_FORMAT fif;

    const char* path = ("res/"+texname).c_str();

    fif = FreeImage_GetFileType(path,0);
    if( FreeImage_FIFSupportsReading(fif))
    {
        texture = FreeImage_Load(fif, path);
        int imgWidth = FreeImage_GetWidth(texture);
        int imgHeight = FreeImage_GetHeight(texture);

        //std::cout << imgWidth << " "<< imgHeight <<"\n";

        glGenTextures( 1, &t );
        std::cout << "\nACTIVE TEXTURE VALUE IS: " << GL_TEXTURE0+t << "\n";
        glActiveTexture(GL_TEXTURE0);
        glBindTexture( GL_TEXTURE_2D, t );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(texture));
        FreeImage_Unload(texture);
        std::cout << "Image file is good\n";
        std::cout << "Loaded: " << texname << "\n";
    }
    else
    {
        std::cout << "File not supported!\n";
    }
}

GLuint Texture::getTexture(){
    return t;
}

std::string Texture::getName(){
    return name;
}
