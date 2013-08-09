#include "ResourceManager.h"
#include <FreeImage.h>
#include "Texture.h"

ResourceManager::ResourceManager(){
    FreeImage_Initialise();
}

ResourceManager::~ResourceManager(){
    FreeImage_DeInitialise();
}

void ResourceManager::loadTexture(){
    textures_vec.push_back(new Texture());
}

void ResourceManager::loadMusic(){

}

void ResourceManager::loadSFX(){

}

void ResourceManager::getMusic(){

}

FIBITMAP* ResourceManager::getTexture(){
    return (*textures_vec.begin())->getTexture();
}

void ResourceManager::getSFX(){

}
