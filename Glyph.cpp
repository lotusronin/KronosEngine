#include "Glyph.h"
#include <iostream>

Glyph::Glyph(char letter, FT_GlyphSlot gs) : glyph_name(letter)
{
    height = gs->bitmap.rows;
    width = gs->bitmap.width;
    int sz = width*height;
    top = gs->bitmap_top;
    left = gs->bitmap_left;

    for(int i = 0; i < sz; i++)
    {
        //std::cout << gs->bitmap.buffer[i] << " ";
        buffer.push_back(gs->bitmap.buffer[i]);
    }
    //std::cout << "\n";
    //int a;
    //std::cin >> a;
    //ogl stuff
    /*glGenBuffers(1, &vbo);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(GL_TEXTURE_2D, &texture);*/
    std::cout << "Created glyph for character '" << letter << "'\n";
}

Glyph::~Glyph()
{
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

void Glyph::render(float x, float y)
{
   /*
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    GLfloat box[4][4] = {
        { x, y, 0, 0},
        { x+width/10, y, 1, 0},
        { x+width/100, y+rows/100, 1, 1},
        { x, y+rows/10, 0, 1},
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_QUADS, 0, 4);*/

    //std::cout << "Font Rendering code goes here!!!\n";
}
