#include "PhysicsSquare.h"
#include "Vector.h"
#include <math.h>

#define PI 3.14159265

PhysicsSquare::PhysicsSquare(float x, float y, int s) : sz(s), mass(1)
{
    init(x, y);
}

PhysicsSquare::PhysicsSquare(float x, float y, int s, float m) : sz(s), mass(m)
{
    init(x, y);
}

PhysicsSquare::~PhysicsSquare()
{
}

void PhysicsSquare::init(float x, float y)
{
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(x+sz);
    coords.push_back(y);
    coords.push_back(x+sz);
    coords.push_back(y+sz);
    coords.push_back(x);
    coords.push_back(y+sz);
    forces[0] = 0;
    forces[1] = 0;
}

std::vector<float>* PhysicsSquare::getCoords()
{
    return &coords;
}

float PhysicsSquare::getMass()
{
    return mass;
}

float PhysicsSquare::getSize()
{
    return sz;
}

float PhysicsSquare::getVelx()
{
    return (float)velocity[0]*cos(velocity[1]*PI/180);
}

float PhysicsSquare::getVely()
{
    return (float)velocity[0]*sin(velocity[1]*PI/180);
}

void PhysicsSquare::addForce(float fx, float fy)
{
    forces[0] += fx;
    forces[1] += fy;
}

void PhysicsSquare::update()
{
}
