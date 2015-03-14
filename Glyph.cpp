#include "Glyph.h"
#include <iostream>

Glyph::Glyph(char letter, FT_GlyphSlot gs) : glyph_name(letter)
{
    height = gs->bitmap.rows;
    width = gs->bitmap.width;
    int sz = width*height;
    top = gs->bitmap_top;
    left = gs->bitmap_left;
    advance = gs->advance.x;

    for(int i = 0; i < sz; i++)
    {
        //std::cout << gs->bitmap.buffer[i] << " ";
        buffer.push_back(gs->bitmap.buffer[i]);
    }
    //std::cout << "\n";
    //int a;
    //std::cin >> a;
    //ogl stuff
    glGenBuffers(1, &vbo);
    /*float arr[16] = {0,0.3f,0,1,
                     0.07f,0.3f,1,1,
                     0.07f,0.4f,1,0,
                     0,0.4f,0,0};
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);*/

    std::cout << "Created glyph for character '" << letter << "'\n";
}

Glyph::~Glyph()
{
    glDeleteBuffers(1, &vbo);
}

char Glyph::getName()
{
    return glyph_name;
}

unsigned char* Glyph::getBuffer()
{
    return &buffer[0];
}

int Glyph::getHeight()
{
    return height;
}

int Glyph::getWidth()
{
    return width;
}

void Glyph::render(float x, float y, Shader* s)
{
    setPos(x,y,0.06f);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindTexture(GL_TEXTURE_2D, texture);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindTexture(GL_TEXTURE_2D, texture);
/*
    GLfloat box[4][4] = {
        { x, y, 0, 0},
        { x+width/10, y, 1, 0},
        { x+width/100, y+rows/100, 1, 1},
        { x, y+rows/10, 0, 1},
    };*/
    GLuint loc = glGetUniformLocation(s->shaderProgram, "myTexture");

    /*
    ** Make Sure all samplers are set with glUniform1i calls
    */
    glUniform1i(loc, 0);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_QUADS, 0, 4);

    //std::cout << "Font Rendering code goes here!!!\n";
}

void Glyph::setTexture(GLuint n)
{
    texture = n;
}

void Glyph::setPos(float x, float y, float sz)
{
    float arr[16] = {x,y,0,1,
                     x+sz,y,1,1,
                     x+sz,y+sz,1,0,
                     x,y+sz,0,0};
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_DYNAMIC_DRAW);
}
