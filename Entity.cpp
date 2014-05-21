#include "Entity.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include "Shader.h"

Entity::Entity(float x, float y, float sz)
{
    //initial values
    float u=0, v=0;
    ptransmat = new TranslationMatrix();

    verts.push_back(x); //0
    verts.push_back(y); //1
    verts.push_back(u);
    verts.push_back(v);
    verts.push_back(x+sz); //4
    verts.push_back(y);  //5
    verts.push_back(u+1);
    verts.push_back(v);
    verts.push_back(x+sz); //8
    verts.push_back(y+sz); //9
    verts.push_back(u+1);
    verts.push_back(v+1);
    verts.push_back(x);  //12
    verts.push_back(y+sz); //13
    verts.push_back(u);
    verts.push_back(v+1);
    stats.push_back(sz);

    /*std::cout << verts.at(0) << " =x " << verts.at(1) << " =y\n";
    std::cout << verts.at(4) << " =x " << verts.at(5) << " =y\n";
    std::cout << verts.at(8) << " =x " << verts.at(9) << " =y\n";
    std::cout << verts.at(12) << " =x " << verts.at(13) << " =y\n";*/


    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(float), &verts[0], GL_STATIC_DRAW);


    e = glGetError();
    if(e != GL_NO_ERROR)
    {
        std::cout << "Error with Binding Buffers!\n" << e << "\n";
    }
}

void Entity::setTexture(GLuint img)
{
    //std::cout << "Setting TextureID to be: " << img+GL_TEXTURE0 << "\n";
    texture = img;
}

std::string Entity::getTexName()
{
    return texname;
}

void Entity::setTexName(const std::string& n)
{
    //std::cout << "Setting Texture name to be: " << n << "\n";
    texname = n;
}

void Entity::draw(Shader* s)
{
    glActiveTexture(GL_TEXTURE0);

    /*  There is something From this point down the the error check that is wrong causing opengl to
    **  throw an GL_INVALID_OPERATION error but the drawing seems fine. Need to find which function(s) causes this?
    */

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(sizeof(GLfloat)*2));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

    //s->enable();
    GLint loc = glGetUniformLocation(s->shaderProgram, "myTexture");
    GLint transloc = glGetUniformLocation(s->shaderProgram, "transformation");
    //std::cout << "\nDrawing Entity...\nTexName: " << texname << "\nTextureID: " << texture << "\n";

    glUniformMatrix4fv(transloc, 1, GL_FALSE, ptransmat->mat);

	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1f(loc, 0); //location of uniform, value (texture unit (GL_TEXTURE"0+n"))

	glDrawArrays(GL_QUADS, 0, 4);
	e = glGetError();
    if(e != GL_NO_ERROR)
    {
        //std::cout << "Error with Drawing!\n" << e << "\n";
    }
}

Entity::~Entity()
{
    delete ptransmat;
    glDeleteBuffers(1, &vbo);
    e = glGetError();
    if(e != GL_NO_ERROR)
    {
        std::cout << "Error with glDeleteBuffers()!\n" << e << "\n";
    }
}
