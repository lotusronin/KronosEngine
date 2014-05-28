#ifndef GLYPH_H
#define GLYPH_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

class Glyph
{
private:
    char glyph_name;
    std::vector<unsigned char> buffer;
    int height, width;
    FT_Int top, left;
    GLuint texture;
    GLuint vbo;
public:
    Glyph(char letter, FT_GlyphSlot gs);
    ~Glyph();
    char getName();
    unsigned char* getBuffer();
    int getHeight();
    int getWidth();
    void render(float x, float y);
};

#endif // GLYPH_H
