#ifndef OBJECT_H
#define OBJECT_H
#include <cstdlib>
#include "Vector.h"

class Object{
private:
    int verts[8];
    Vec2* vec;
    int hspeed, vspeed, xcent, ycent;
public:
    Object();
    ~Object();
    void draw();
    void addForce(Vec2 *pvec);
    void stop(bool x, bool y);
    Vec2* getSpeed();
    int* getVerts();
    void moveobj(int dir);
};

class immobileObject{
private:
    int verts[8];
    Vec2* vec;
public:
    immobileObject();
    ~immobileObject();
    Vec2* getSpeed();
    int* getVerts();
    void draw();
};

#endif
