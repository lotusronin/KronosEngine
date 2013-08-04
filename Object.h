#ifndef OBJECT_H
#define OBJECT_H
#include <cstdlib>
#include "Vector.h"

class Object{
protected:
    int verts[8];
    Vec2* vec;
public:
    Object();
    ~Object();
    Vec2* getSpeed();
    int* getVerts();
    void draw();
};

class MobileObject : public Object{
protected:
    int verts[8];
    Vec2* vec;
    int hspeed, vspeed, xcent, ycent;
public:
    MobileObject();
    ~MobileObject();
    void draw();
    void addForce(Vec2 *pvec);
    void stop(bool x, bool y);
    Vec2* getSpeed();
    int* getVerts();
    void moveobj(int dir);
};



#endif
