#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <string>
#include "FontFactory.h"
#include "Glyph.h"
#include "Shader.h"

class GUIManager
{
    FontFactory* ffactory;
public:
    GUIManager();
    ~GUIManager();
    void printString(std::string& s);
};

#endif // GUIMANAGER_H
