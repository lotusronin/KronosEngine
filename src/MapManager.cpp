#include "MapManager.h"
#include "Map.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include "defer.h"

MapManager::MapManager()
{}

MapManager::~MapManager()
{
    for(auto it : MapList){
        delete it;
    }
}

void MapManager::newMap(std::string name)
{

    bool exists = false;
    for(auto it : MapList){
            if(it->getMapName().compare(name) == 0){
                exists = true;
            }
    }

    if(!exists)
    {
        MapList.push_back(new Map(name));
    }
}

void MapManager::addToMap(std::string obj)
{
    Map* temp;
    for(auto it : MapList){
            if(it->getMapName().compare(currentMap) == 0){
                temp = it;
            }
    }
    temp->addToMap(obj);
    //(*MapList.begin())->addToMap(obj);
}

std::vector<std::string>* MapManager::getMapData()
{
    for(auto it : MapList){
            if(it->getMapName().compare(currentMap) == 0){
                return it->getMap();
            }
    }

    return nullptr;
    //return (*MapList.begin())->getMap();
}

std::string MapManager::getMapName()
{
    return currentMap;
}

void MapManager::loadMap(std::string fname, ResourceManager* resman, EntityManager* entityman, DataReader* parser)
{
    fname = "./res/map/" + fname;
    std::cout << "Loading File: " << fname << "\n";
    std::ifstream ifs(fname, std::ios::binary);
    std::string s;
    ifs >> s;
    currentMap = s;
    if(!mapExists(s))
    {
        newMap(s);
        ifs >> s;
        if(s.compare(0,5,"music") == 0) {
            addMusictoMap(s.substr(6));
            ifs >> s;
        } else {
            addMusictoMap("");
        }
        while(s.compare("mapend")){
            //std::cout<< s << "\n";
            addToMap(s);
            ifs >> s;
        }
    }
    else
    {
        std::cout << "Map Already exists!!!!\n";
    }
    ifs.close();
    std::cout << "File Loaded \n";

    //Pulled in from GameManager
    std::vector<std::string>* currentMap = getMapData();

    //Parse the String
    std::cout << "Map Name: "<< getMapName() << "\n";
    std::cout << "Map Music: " << getMusicName() << "\n";
    resman->loadMusic(getMusicName());

    for(auto it : (*currentMap)){
        char *cstr = new char[it.length() + 1];
        defer { delete[] cstr; };
        std::strcpy (cstr, it.c_str());
        char * p = std::strtok (cstr,",");
        //std::cout << p << "\n";
        float x = (float)atof(p);
        //std::cout << "The value of x is: " << x << "\n";


        p = std::strtok(NULL,",");
        //std::cout << p << "\n";
        float y = (float)atof(p);
        //std::cout << "The value of y is: " << y << "\n";

        p = std::strtok(NULL,",");
        //std::cout << p << "\n";

        std::string pstring = p;
        std::cout << "\n" << pstring << " at " << x << "," << y << "\n";

        parser->loadObj(pstring);
        defer { parser->closeObj(); };

        pstring = parser->getValue("size");
        float sz = (float)atof(pstring.c_str());
        pstring = parser->getValue("entity_type");

        if(!strcmp(pstring.c_str(),"Character"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            entityman->addChar(x,y,sz,s);
        }
        else if(!strcmp(pstring.c_str(),"Ground"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            entityman->addGrd(x,y,sz,s);
        }
        else if(!strcmp(pstring.c_str(), "Item"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            entityman->addItem(x,y,sz,s);
        }
    }
}


void MapManager::saveMap(const char* fname)
{
    std::cout << "Generating a new Map file\n";
	std::ofstream ofs(fname, std::ios::binary);
	std::cout << "Writing to file...\n";
	std::string MapName = getMapName();
	ofs << MapName << " ";
	std::vector<std::string>* pMapData = getMapData();
    for(auto it : (*pMapData)){
        ofs << it;
        ofs << " ";
    }
    ofs << "mapend";
	std::cout << "Done\n";
	ofs.close();
}


void MapManager::showMap()
{
    (*MapList.begin())->showData();
}

bool MapManager::mapExists(std::string name)
{
    for(auto it : MapList){
            if(it->getMapName().compare(name) == 0){
                return true;
            }
    }
    return false;
}

void MapManager::addMusictoMap(std::string music) {
    Map* temp;
    for(auto it : MapList){
            if(it->getMapName().compare(currentMap) == 0){
                temp = it;
            }
    }
    temp->addMusictoMap(music);
}

std::string MapManager::getMusicName() {
    for(auto it : MapList){
            if(it->getMapName().compare(currentMap) == 0){
                return it->getMusicName();
            }
    }

    return "";
}
