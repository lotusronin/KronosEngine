#include "FontFactory.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

FontFactory::FontFactory()
{
    error = FT_Init_FreeType(&library);
    if(error)
    {
        std::cout << "There was an error initializing the font library!\n";
    }

    error = FT_New_Face(library, "/usr/share/fonts/TTF/arial.ttf", 0, &face);
    if(error)
    {
        std::cout << "There was an error opening the font file!\n";
    }

    /*error = FT_Set_Char_Size(face, 0, 16*64, 0, 0);
    if(error)
    {
        std::cout << "There was an error setting the character size!\n";
    }*/

    FT_Set_Pixel_Sizes(face, 0, 18);


    std::cout << "FontFactory initialized!!\n";
}

FontFactory::~FontFactory()
{
    for(std::vector<Glyph*>::iterator it = alphabet.begin(); it != alphabet.end(); it++)
    {
        delete (*it);
    }
    for(std::vector<Texture*>::iterator it = fontTexture.begin(); it != fontTexture.end(); it++)
    {
        delete (*it);
    }
    alphabet.erase(alphabet.begin(), alphabet.end());
    fontTexture.erase(fontTexture.begin(), fontTexture.end());

    FT_Done_Face(face);
    FT_Done_FreeType(library);
}

Glyph* FontFactory::getLetter(char letter)
{
    //If it exists, return Glyph*
    for(std::vector<Glyph*>::iterator it = alphabet.begin(); it != alphabet.end(); it++)
    {
        if((*it)->getName() == letter)
        {
            return *it;
        }
    }
    //else call make letter if glyph isn't already made
    makeLetter(letter);
    return alphabet.back();
}

void FontFactory::makeLetter(char letter)
{
    //std::cout << "Making new glyph for '" << letter << "'\n";
    //make glyph of letter
    error = FT_Load_Char(face, letter, FT_LOAD_RENDER);
    if(error)
    {
        std::cout << "Error loading character '" << letter << "'!\n";
    }

    gs = face->glyph;
    try{
        alphabet.push_back(new Glyph(letter, gs));
        int w, h;
        w = alphabet.back()->getWidth();
        h = alphabet.back()->getHeight();
        std::string s = "";
        s.push_back(letter);
        fontTexture.push_back(new Texture(s));
        fontTexture.back()->FontTexture(w, h, alphabet.back()->getBuffer());

        alphabet.back()->setTexture(fontTexture.back()->getTexture());
    }
    catch(std::bad_alloc& ba)
    {
        std::cout << "Error making glyph " << letter << "\n";
        exit(1);
    }
    //std::cout << "makeLetter() Finished\n";
    //std::cout << "Finished making letter " << letter << "\n";
}

void FontFactory::renderLetter(char letter, float x, float y, Shader* s)
{
    Glyph* g = getLetter(letter);
    //std::cout << "beginning to render letter " << letter << "\n";
    //std::cout << "Glyph* g letter = " << g->getName() << "\n";
    g->render(x, y, s);
}
