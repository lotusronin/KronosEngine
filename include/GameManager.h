#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Window.h"
#include "KeyListener.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "ScriptManager.h"
#include "MapManager.h"
#include "DataReader.h"
#include "Renderer.h"
#include "FontFactory.h"
#include "EventManager.h"

class GameManager{
private:
    std::string s;
public:
    Window* win_main;
    KeyListener* listener;
    EntityManager* entityman;
    ResourceManager* resman;
    ScriptManager* scriptman;
    MapManager* mapman;
    DataReader* parser;
    Renderer* renderer;
    FontFactory* ffactory;
    EventManager* eventman;
    GameManager();
    ~GameManager();
    void setMap(std::string arr);
    void init();
    void LoadMap();
    int run();
};

#endif
