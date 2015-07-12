#include <vector>
#include <string>
#include "Map.h"
#include <iostream>

Map::Map(std::string _map_name) : map_name(_map_name)
{}

Map::~Map()
{}

void Map::addToMap(std::string obj)
{
    layout.push_back(obj);
}

std::string Map::getMapName()
{
    return map_name;
}

std::vector<std::string>* Map::getMap()
{
    return &layout;
}

void Map::showData()
{
    for(auto it : layout){
            std::cout << it << "\n";
    }
}

void Map::addMusictoMap(std::string music) {
    music_name = music;
}

std::string Map::getMusicName() {
    return music_name;
}

void Map::addBkgtoMap(std::string bkg) {
    m_bkg = bkg;
}

std::string Map::getBkgName() {
    return m_bkg;
}
