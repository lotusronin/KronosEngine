#include "ResourceManager.h"
#include "Texture.h"
#include "Sound.h"
#include <iostream>
#include <string>

ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{
    for(std::vector<Texture*>::iterator it = tvec.begin(); it != tvec.end(); it++){
            delete (*it);
    }

    for(std::vector<Sound*>::iterator it = svec.begin(); it != svec.end(); it++){
            delete (*it);
    }
}

void ResourceManager::loadTexture(const std::string& texname)
{
    bool exists = false;
    for(std::vector<Texture*>::iterator it = tvec.begin(); it != tvec.end(); it++){
            if((*it)->getName().compare(texname) == 0){
                exists = true;
            }
    }

    if(!exists){
        tvec.push_back(new Texture(texname));
    }else{
        std::cout << "Texture Already loaded!\n";
    }
}

void ResourceManager::loadMusic(const std::string& musname)
{
    bool exists = false;
    for(std::vector<Sound*>::iterator it = svec.begin(); it != svec.end(); it++){
            if((*it)->getName().compare(musname) == 0){
                exists = true;
            }
    }

    if(!exists){
        svec.push_back(new Sound(musname));
    }else{
        std::cout << "Sound Already loaded!\n";
    }
}

void ResourceManager::loadSFX()
{}

void ResourceManager::getMusic()
{
    if(!(*svec.begin())->isPlaying()){
        (*svec.begin())->Play();
    }
}

GLuint ResourceManager::getTexture(const std::string& texname)
{

    for(std::vector<Texture*>::iterator it = tvec.begin(); it != tvec.end(); it++){
            if((*it)->getName().compare(texname) == 0){
                return (*it)->getTexture();
            }
    }
    return 0;

}

void ResourceManager::getSFX()
{}
