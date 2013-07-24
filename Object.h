#ifndef OBJECT_H
#define OBJECT_H
#include <cstdlib>
#include "Vector.h"

class Object{
private:
    int verts[6];
    Vec2* vec;
    int hspeed, vspeed;
public:
    Object();
    ~Object();
    void draw();
    void addForce(Vec2 *pvec);
    void moveobj(int dir);
};

#endif
