#ifndef KEYLISTENER_H
#define KEYLISTENER_H
#include <cstdlib>
#include <SDL/SDL.h>

class KeyListener{

public:
    KeyListener();
    ~KeyListener();
    int query();
    int getKeys();
    int save();

};

#endif
