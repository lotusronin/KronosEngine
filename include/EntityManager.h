#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#include "Entity.h"
#include "Character.h"
#include "Ground.h"
#include "Item.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "MapManager.h"
#include "Shader.h"
#include "PlayerControl.h"
#include "KeyListener.h"
#include "FontFactory.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

class EntityManager{
protected:
    std::vector<Ground*> groundList;
    std::vector<Character*> characterList;
    std::vector<Item*> itemList;
    Camera* cam;
    ResourceManager* resman;
    PhysicsManager* einstein;
    PlayerControl* controller;
    FontFactory* ffactory;
    ScriptManager* scriptman;

public:
    //std::string mapname;
    EntityManager();
    ~EntityManager();
    void addChar(float x, float y, float sz, std::string &texname);
    void addGrd(float x, float y, float sz, std::string &texname);
    void addItem(float x, float y, float sz, std::string &texname);
    void clearObjects();
    void deleteObj();
    void draw(Shader* shader, Shader* textshader, MapManager* mapman);
    void applyPhysics();
    void updateCam();
    void saveMap(MapManager* mapman);
    void setMap(std::string arr);
    void setControllerListener(KeyListener* pkl);
    void setResourceManager(ResourceManager* prm);
    void setScriptManager(ScriptManager* psm);
    void showInfo();
    std::string fpsVal;
};

#endif
