#ifndef ENTITY_H
#define ENTITY_H

#include <cstdlib>
#include <vector>
#include <GL/glu.h>
#include <GL/gl.h>
/*
    This is the generic entity class. All other entity types (item, ground, character, decal) will be derived from this one.
    Never instantiate Entity objects!!! Always use a subclass.

*/

class Entity{
protected:
    std::vector<float> verts; //Will be either 6 or 8 verts (triangle or square)
    std::vector<float> stats; //Will contain: size, radius, mass, hspeed, vspeed etc
    GLuint texture;
public:
    void setTexture(GLuint img);
    void draw();
    Entity(float x, float y, float sz);
    virtual ~Entity();
};

#endif // ENTITY_H
