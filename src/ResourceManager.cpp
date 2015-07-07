#include "ResourceManager.h"
#include "defer.h"
#include "Texture.h"
#include "Sound.h"
#include <iostream>
#include <string>
#include <FreeImage.h>

ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{
    for(auto it : tvec){
            delete it;
    }

    /*GLuint e = glGetError();
    if(e != GL_NO_ERROR)
    {
        std::cout << "Error with Texture Clean-up!\n" << e << "\n";
    }
    else
    {
        std::cout << "Textures all cleaned up nicely!\n";
    }*/

    for(auto it : svec){
            delete it;
    }
    tvec.erase(tvec.begin(), tvec.end());
    svec.erase(svec.begin(), svec.end());
    

    /*
     *  Clean up openal
     */
    alcMakeContextCurrent(NULL);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
	std::cout << "OpenAL all cleaned up!\n";
}

void ResourceManager::loadTexture(const std::string& texname)
{
    bool exists = false;
    for(auto it : tvec){
            if(it->getName().compare(texname) == 0){
                exists = true;
            }
    }

    if(!exists){

        FIBITMAP* texture;
        FREE_IMAGE_FORMAT fif;
        int imgWidth;
        int imgHeight;

        const char* path = ("res/texture/"+texname).c_str();

        fif = FreeImage_GetFileType(path,0);

        if( FreeImage_FIFSupportsReading(fif)){
            texture = FreeImage_Load(fif, path);
            texture = FreeImage_ConvertTo32Bits(texture);
            imgWidth = FreeImage_GetWidth(texture);
            imgHeight = FreeImage_GetHeight(texture);
            tvec.push_back(new Texture(texname));
            tvec.back()->FITexture(imgWidth, imgHeight, texture);
            FreeImage_Unload(texture);
        }
        else{
            std::cout << "File not supported!\n";
        }
    }
    else{
        std::cout << "Texture Already loaded!\n";
    }
}

void ResourceManager::loadMusic(const std::string& musname)
{
    bool exists = false;
    for(auto it : svec){
            if(it->getName().compare(musname) == 0){
                exists = true;
            }
    }

    if(!exists){
        loadOgg(musname);
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

    for(auto it : tvec){
            if(it->getName().compare(texname) == 0){
                return it->getTexture();
            }
    }
    return 0;

}

void ResourceManager::getSFX()
{}

void ResourceManager::initSound() {
    m_alError = false;
    m_device = alcOpenDevice(NULL);
	if(!m_device)
	{
		std::cout << "Error opening sound device!!!\n";
		m_alError = true;
	}

	m_context = alcCreateContext(m_device, NULL);

	if(!alcMakeContextCurrent(m_context))
	{
		std::cout << "Error setting up context!!!\n";
		m_alError = true;
	}

    if(m_alError) {
        std::cout << "Error with openAL!!\n";
    }
}

void ResourceManager::loadOgg(const std::string& filename) {

    vorbis_info* pInfo;
    OggVorbis_File oggFile;

    ov_fopen(("res/sound/"+filename).c_str(), &oggFile);
    defer { ov_clear(&oggFile);};

    pInfo = ov_info(&oggFile, -1);
    ALenum format;
    if(pInfo->channels == 1) {
       format = AL_FORMAT_MONO16; 
    } else {
        format = AL_FORMAT_STEREO16;
    }

    ALsizei freq = pInfo->rate;

    std::vector<char> musicBuffer;
    char buffer[4096];
    int bitstream;
    long bytes;
    while((bytes = ov_read(&oggFile, buffer, 4096, 0, 2, 1, &bitstream)) > 0) {
        musicBuffer.insert(musicBuffer.end(), buffer, buffer+bytes);
    }
    
    svec.push_back(new Sound(filename, m_alError, format, (ALvoid*)&musicBuffer[0], (ALsizei) musicBuffer.size(), freq));
}
