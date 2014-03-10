#ifndef OBJECT_H
#define OBJECT_H
#include <cstdlib>
#include "Vector.h"
#include <GL/glew.h>
#include <GL/gl.h>

class Object{
protected:
    int verts[8];
    Vec2* vec;
    GLuint texture;

public:
    Object(int x, int y, int sz);
    virtual ~Object();
    Vec2* getSpeed();
    int* getVerts();
    void draw();
    void setTexture(GLuint img);
};

class MobileObject : public Object{
protected:
    int hspeed, vspeed, xcent, ycent;
    bool onground;
public:
    MobileObject(int x, int y, int sz);
    virtual ~MobileObject();
    void draw();
    void addForce(Vec2 *pvec);
    void stop(bool x, bool y);
    Vec2* getSpeed();
    int* getVerts();
    void moveobj();
    void setonground(bool b);
    bool isonground();
    int getCenterX();
    int getCenterY();
};



#endif
