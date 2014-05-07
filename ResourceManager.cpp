#include "ResourceManager.h"
#include "Texture.h"
#include "Sound.h"
#include <iostream>

ResourceManager::ResourceManager(){
}

ResourceManager::~ResourceManager(){
    for(std::vector<Texture*>::iterator it = tvec.begin(); it != tvec.end(); it++){
            delete (*it);
    }

    for(std::vector<Sound*>::iterator it = svec.begin(); it != svec.end(); it++){
            delete (*it);
    }
}

void ResourceManager::loadTexture(){
    tvec.push_back(new Texture());
}

void ResourceManager::loadMusic(){
    svec.push_back(new Sound("test.wav"));
}

void ResourceManager::loadSFX(){

}

void ResourceManager::getMusic(){
    if(!(*svec.begin())->isPlaying()){
        (*svec.begin())->Play();
    }
}

GLuint ResourceManager::getTexture(){
    return (*tvec.begin())->getTexture();

}

void ResourceManager::getSFX(){

}
