#ifndef CHARACTER_H
#define CHARACTER_H


#include "Entity.h"
#include "PhysicsSquare.h"
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

/*
    This is the Character Entity used for all player and npc objects.

*/


class Character : public Entity{
public:
    Character(float x, float y, float sz);
    ~Character();
    PhysicsSquare* pSquare;
    void draw();
    void draw(Shader* s);
    float getCenterX();
    float getCenterY();
    PhysicsSquare* getObj();
    void update();
};

#endif // CHARACTER_H
