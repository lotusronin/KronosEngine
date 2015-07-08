#ifndef  MAPMANAGER_H
#define MAPMANAGER_H

#include "Map.h"
#include <vector>

class MapManager{
protected:
    std::vector<Map*> MapList;
    std::string currentMap;
public:
    MapManager();
    ~MapManager();
    void loadMap(std::string fname);
    void saveMap(const char* fname);
    std::vector<std::string>* getMapData();
    std::string getMapName();
    void newMap(std::string name);
    void addToMap(std::string obj);
    void showMap();
    bool mapExists(std::string name);
    void addMusictoMap(std::string music);
    std::string getMusicName();
};


#endif // MAPMANAGER_H
