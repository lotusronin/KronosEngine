#ifndef PHYSICSSQUARE_H
#define PHYSICSSQUARE_H

#include <vector>
#include <cstdlib>
#include "Vector.h"

class PhysicsSquare
{
private:
    float velocity[2];
    float forces[2];
    float sz;
    float mass;
    std::vector<float> coords;
    void init(float x, float y);
public:
    PhysicsSquare(float x, float y, int s);
    PhysicsSquare(float x, float y, int s, float m);
    ~PhysicsSquare();
    std::vector<float>* getCoords();
    float getMass();
    float getSize();
    float getVelx();
    float getVely();
    void addForce(float fx, float fy);
    void update();
};

#endif // PHYSICSSQUARE_H
