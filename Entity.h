#ifndef ENTITY_H
#define ENTITY_H

#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Shader.h"
#include "Matrix.h"

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
    GLenum e;
public:
    void setTexture(GLuint img);
    void draw(Shader* s);
    std::string getTexName();
    void setTexName(const std::string& n);
    Entity(float x, float y, float sz);
    virtual ~Entity();

    //Translation Matrix
    TranslationMatrix* ptransmat;
};

#endif // ENTITY_H
