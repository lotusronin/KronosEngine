#include "Character.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdio.h>

//10px / m
#define M2PIX 10

Character::Character(float x, float y, float sz) : Entity(x*5, y*5, sz*5)
{
    pSquare = new PhysicsSquare(x*5, y*5, sz*5);
}

Character::~Character()
{
    delete pSquare;
}

float Character::getCenterX()
{
    std::vector<float>* coords = pSquare->getCoords();
    return ((coords->at(2) - coords->at(0))/2 + coords->at(0));
    //return ((verts.at(2) - verts.at(0))/2 + verts[0]);
}

float Character::getCenterY()
{
    std::vector<float>* coords = pSquare->getCoords();
    //return ((verts.at(5) - verts.at(3))/2 + verts[3]);
    return ((coords->at(5) - coords->at(3))/2 + coords->at(3));
}

PhysicsSquare* Character::getObj()
{
    return pSquare;
}
