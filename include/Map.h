#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>

class Map{
protected:
    std::string map_name;
    std::vector<std::string> layout;
    std::string music_name;
public:
    Map(std::string _map_name);
    ~Map();
    void addToMap(std::string obj);
    std::vector<std::string>* getMap();
    std::string getMapName();
    void showData();
    void addMusictoMap(std::string music);
    std::string getMusicName();
};

#endif
