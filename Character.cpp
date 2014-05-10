#include "Character.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdio.h>

//10px / m
#define M2PIX 10

Character::Character(float x, float y, float sz) : Entity(x*5, y*5, sz*5)
{
    pSquare = new PhysicsSquare(x, y, sz);
}

Character::~Character()
{
    delete pSquare;
}

void Character::draw(Shader* s)
{
    Entity::draw(s);
}

void Character::draw()
{
    /*glUseProgram(0);
    glBegin(GL_QUADS);
        glColor3f(0,1,0);
        glVertex3f(verts.at(0),verts.at(1),0);
        glColor3f(1,0,0);
        glVertex3f(verts.at(4),verts.at(5),0);
        glColor3f(0,0,1);
        glVertex3f(verts.at(8),verts.at(9),0);
        glColor3f(1,1,1);
        glVertex3f(verts.at(12),verts.at(13),0);
    glEnd();*/
}

float Character::getCenterX()
{
    return ((verts.at(2) - verts.at(0))/2 + verts[0]);
}

float Character::getCenterY()
{
    return ((verts.at(5) - verts.at(3))/2 + verts[3]);
}

PhysicsSquare* Character::getObj()
{
    return pSquare;
}

void Character::update()
{
    pSquare->update();
    std::vector<float> *pCoords = pSquare->getCoords();
    float s = pSquare->getSize();

    verts.at(0) = (*pCoords).at(0);
    verts.at(1) = (*pCoords).at(1);
    verts.at(2) = (*pCoords).at(2+s);
    verts.at(3) = (*pCoords).at(3);
    verts.at(4) = (*pCoords).at(4);
    verts.at(5) = (*pCoords).at(5);
    verts.at(6) = (*pCoords).at(6);
    verts.at(7) = (*pCoords).at(7);
//    verts.push_back(x+sz);
//    verts.push_back(y+sz);
//    verts.push_back(x);
//    verts.push_back(y+sz);
//    stats.push_back(sz);


}
