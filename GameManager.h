#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Window.h"
#include "KeyListener.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include <time.h>

class GameManager{
private:
    struct timeval t;
    double t1, t2;
    std::string s;
public:
    Window* win_main;
    KeyListener* listener;
    EntityManager* entityman;
    GameManager();
    ~GameManager();
    void setMap(std::string arr);
    void init();
    int run();
    void calcfps();
};

#endif
