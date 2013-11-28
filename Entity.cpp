#include "Entity.h"
#include <GL/gl.h>
#include <GL/glu.h>

Entity::Entity(float x, float y, float sz)
{
    //initial values
    verts.push_back(x);
    verts.push_back(y);
    verts.push_back(x+sz);
    verts.push_back(y);
    verts.push_back(x+sz);
    verts.push_back(y+sz);
    verts.push_back(x);
    verts.push_back(y+sz);
    stats.push_back(sz);
}

void Entity::setTexture(GLuint img)
{
    texture = img;
}

void Entity::draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);

        glTexCoord2d(0.0, 1.0);
        glVertex3f(verts.at(0),verts.at(1),0);
        glTexCoord2d(1.0, 1.0);
        glVertex3f(verts.at(2),verts.at(3),0);
        glTexCoord2d(1.0, 0.0);
        glVertex3f(verts.at(4),verts.at(5),0);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(verts.at(6),verts.at(7),0);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

Entity::~Entity()
{
}
