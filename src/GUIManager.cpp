#include "GUIManager.h"

GUIManager::GUIManager()
{
    ffactory = new FontFactory();
}

GUIManager::~GUIManager()
{
    delete ffactory;
}
