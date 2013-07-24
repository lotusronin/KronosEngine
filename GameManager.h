#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Window.h"
#include "KeyListener.h"
#include "Object.h"

class GameManager{
public:
    Window* win_main;
    KeyListener* listener;
    Object* triangle;
    Vec2* gravity;
    GameManager();
    ~GameManager();
    void init();
    int run();

};

#endif
