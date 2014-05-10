#ifndef ENTITY_H
#define ENTITY_H

#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Shader.h"
/*
    This is the generic entity class. All other entity types (item, ground, character, decal) will be derived from this one.
    Never instantiate Entity objects!!! Always use a subclass.

*/

class Entity{
protected:
    std::vector<float> verts; //Will be either 6 or 8 verts (triangle or square)
    std::vector<float> stats; //Will contain: size, radius, mass, hspeed, vspeed etc
    GLuint texture, vbo;
    std::string texname;
public:
    void setTexture(GLuint img);
    void draw(Shader* s);
    std::string getTexName();
    void setTexName(std::string n);
    Entity(float x, float y, float sz);
    virtual ~Entity();
};

#endif // ENTITY_H
