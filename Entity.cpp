#include "Entity.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include "Shader.h"

Entity::Entity(float x, float y, float sz)
{
    //initial values
    float u=0, v=0;
    verts.push_back(x);
    verts.push_back(y);
    verts.push_back(0);
    verts.push_back(u);
    verts.push_back(v);
    verts.push_back(x+sz);
    verts.push_back(y);
    verts.push_back(0);
    verts.push_back(u+1);
    verts.push_back(v);
    verts.push_back(x+sz);
    verts.push_back(y+sz);
    verts.push_back(0);
    verts.push_back(u+1);
    verts.push_back(v+1);
    verts.push_back(x);
    verts.push_back(y+sz);
    verts.push_back(0);
    verts.push_back(u);
    verts.push_back(v+1);
    stats.push_back(sz);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(float), &verts.front(), GL_STATIC_DRAW);

    GLenum e = glGetError();
    if(e != GL_NO_ERROR)
    {
        std::cout << "There was an error binding the data!!!!!\n" << e << "\n";
    }
}

void Entity::setTexture(GLuint img)
{
    texture = img;
}

void Entity::draw(Shader* s)
{

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    s->enable();
    GLint loc = glGetUniformLocation(s->shaderProgram, "myTexture");

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1f(loc, 0);

	glDrawArrays(GL_QUADS, 0, 4);
}

Entity::~Entity()
{
}
