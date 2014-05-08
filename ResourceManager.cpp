#include "ResourceManager.h"
#include "Texture.h"
#include "Sound.h"
#include <iostream>
#include <string>

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

void ResourceManager::loadTexture(std::string texname){
    tvec.push_back(new Texture(texname));
}

void ResourceManager::loadMusic(std::string musname){
    svec.push_back(new Sound(musname));
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
