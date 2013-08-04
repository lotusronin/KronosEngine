#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Window.h"
#include "KeyListener.h"
#include "EntityManager.h"
#include "ResourceManager.h"

class GameManager{
public:
    Window* win_main;
    KeyListener* listener;
    EntityManager* Einstein;
    ResourceManager* resMan;
    GameManager();
    ~GameManager();
    void init();
    int run();

};

#endif
