#include "MapManager.h"
#include "Map.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

MapManager::MapManager()
{}

MapManager::~MapManager()
{
    for(std::vector<Map*>::iterator it = MapList.begin(); it != MapList.end(); it++){
        delete (*it);
    }
}

void MapManager::newMap(std::string name)
{

    bool exists = false;
    for(std::vector<Map*>::iterator it = MapList.begin(); it != MapList.end(); it++){
            if((*it)->getMapName().compare(name) == 0){
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
    for(std::vector<Map*>::iterator it = MapList.begin(); it != MapList.end(); it++){
            if((*it)->getMapName().compare(currentMap) == 0){
                temp = (*it);
            }
    }
    temp->addToMap(obj);
    //(*MapList.begin())->addToMap(obj);
}

std::vector<std::string>* MapManager::getMapData()
{
    for(std::vector<Map*>::iterator it = MapList.begin(); it != MapList.end(); it++){
            if((*it)->getMapName().compare(currentMap) == 0){
                return (*it)->getMap();
            }
    }

    return nullptr;
    //return (*MapList.begin())->getMap();
}

std::string MapManager::getMapName()
{
    //return (*MapList.begin())->getMapName();
    return currentMap;
}

void MapManager::loadMap(const char* fname)
{
    std::cout << "Loading File: " << fname << "\n";
    std::ifstream ifs(fname, std::ios::binary);
    std::string s;
    ifs >> s;
    if(!mapExists(s))
    {
        newMap(s);
        currentMap = s;
        ifs >> s;
        while(s.compare("mapend")){
            //std::cout<< s << "\n";
            addToMap(s);
            ifs >> s;
        }
    }
    ifs.close();
    std::cout << "File Loaded \n";
}


void MapManager::saveMap(const char* fname)
{
    std::cout << "Generating a new Map file\n";
	std::ofstream ofs(fname, std::ios::binary);
	std::cout << "Writing to file...\n";
	std::string MapName = getMapName();
	ofs << MapName << " ";
	std::vector<std::string>* pMapData = getMapData();
    for(std::vector<std::string>::iterator it = (*pMapData).begin(); it != (*pMapData).end(); it++){
        ofs << (*it);
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
    for(std::vector<Map*>::iterator it = MapList.begin(); it != MapList.end(); it++){
            if((*it)->getMapName().compare(name) == 0){
                return true;
            }
    }
    return false;
}
