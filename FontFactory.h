#ifndef FONTFACTORY_H
#define FONTFACTORY_H

#include <vector>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Glyph.h"
#include "Texture.h"
#include "Shader.h"

class FontFactory
{
private:
    std::vector<Glyph*> alphabet;
    std::vector<Texture*> fontTexture;
    std::string font_name;
    FT_Library library;
    FT_Face face;
    FT_GlyphSlot gs;
    int error;
public:
    FontFactory();
    ~FontFactory();
    Glyph* getLetter(char letter);
    void makeLetter(char letter);
    void renderLetter(char letter, float x, float y, Shader* s);
};

#endif // FONTFACTORY_H
