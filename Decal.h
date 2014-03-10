#ifndef DECAL_H
#define DECAL_H


#include "Entity.h"
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

/*
    This is the Decal Entity used for all decal objects.
    These are entities are intended to spice up the scenery.
    They have no impact/interaction with the other entities, they are purely aescetic.

*/


class Decal : public Entity{
public:
    Decal();
    ~Decal();
};

#endif // DECAL_H
