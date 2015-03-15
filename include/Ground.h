#ifndef GROUND_H
#define GROUND_H

#include "Entity.h"
#include "PhysicsSquare.h"
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

/*
    This is the Ground Entity used for all ground objects.

*/


class Ground : public Entity{
public:
    PhysicsSquare* pSquare;
    Ground(float x, float y, float sz);
    ~Ground();
    PhysicsSquare* getObj();
    void update();
};

#endif // GROUND_H
