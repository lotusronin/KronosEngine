#include "ResourceManager.h"
#include "Texture.h"
#include <iostream>

ResourceManager::ResourceManager(){
}

ResourceManager::~ResourceManager(){
    for(std::vector<Texture*>::iterator it = tvec.begin(); it != tvec.end(); it++){
            delete (*it);
    }
}

void ResourceManager::loadTexture(){
    tvec.push_back(new Texture());
}

void ResourceManager::loadMusic(){

}

void ResourceManager::loadSFX(){

}

void ResourceManager::getMusic(){

}

GLuint ResourceManager::getTexture(){
    return (*tvec.begin())->getTexture();

}

void ResourceManager::getSFX(){

}
