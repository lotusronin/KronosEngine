#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#include "Entity.h"
#include "Character.h"
#include "Ground.h"
#include "Item.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "Shader.h"
#include "PlayerControl.h"
#include "KeyListener.h"
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

public:
    //std::string mapname;
    EntityManager();
    ~EntityManager();
    void addChar(float x, float y, float sz, std::string &texname);
    void addGrd(float x, float y, float sz, std::string &texname);
    void addItem(float x, float y, float sz, std::string &texname);
    void clearObjects();
    void deleteObj();
    void applyPhysics();
    void updateCam();
    void setMap(std::string arr);
    void setControllerListener(KeyListener* pkl);
    void setResourceManager(ResourceManager* prm);
    void showInfo();
    std::vector<Ground*>* getGroundList();
    std::vector<Character*>* getCharacterList();
    std::vector<Item*>* getItemList();
    Camera* getCamera();
    std::string fpsVal;
};

#endif
