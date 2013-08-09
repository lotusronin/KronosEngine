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
public:
    Window* win_main;
    KeyListener* listener;
    EntityManager* Einstein;
    GameManager();
    ~GameManager();
    void init();
    int run();
    void calcfps();
};

#endif
