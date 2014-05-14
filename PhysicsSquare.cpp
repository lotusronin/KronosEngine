#include "PhysicsSquare.h"
#include "Vector.h"
#include <math.h>
#include <iostream>

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
    velocity[0] = 0;
    velocity[1] = 0;
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
    //return (float)velocity[0]*cos(velocity[1]*PI/180);
    return velocity[0];
}

float PhysicsSquare::getVely()
{
    //return (float)velocity[0]*sin(velocity[1]*PI/180);
    return velocity[1];
}


void PhysicsSquare::addVeloc(float vx, float vy)
{
    //std::cout << "addVeloc was called!!!! vx: " << vx << " vy: " << vy << "\n";
    velocity[0] += vx;
    velocity[1] += vy;
    //std::cout << "Velocityx: " << velocity[0] << " Velocityy: " << velocity[1] << "\n";
    //std::cout << "yvelocity is: "<< velocity[1] << "\n";
}

void PhysicsSquare::setVeloc(float vx, float vy)
{
    //std::cout << "setVeloc was called!!!! vx: " << vx << " vy: " << vy << "\n";
    velocity[0] = vx;
    velocity[1] = vy;
}

void PhysicsSquare::addForce(float fx, float fy)
{
    forces[0] += fx;
    forces[1] += fy;
}


void PhysicsSquare::update()
{
    int counter = 0;
    for(std::vector<float>::iterator it = coords.begin(); it != coords.end(); it++)
    {
        if(counter%2 == 0)
        {
            (*it) += velocity[0];
        }
        else
        {
            (*it) += velocity[1];
        }

        counter++;
    }
}
