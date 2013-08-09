#include "Texture.h"
#include <FreeImage.h>

Texture::Texture(){
    texture = FreeImage_Load(FIF_BMP, "PlatformerGround.bmp", BMP_DEFAULT);
}

FIBITMAP* Texture::getTexture(){
    return texture;
}
