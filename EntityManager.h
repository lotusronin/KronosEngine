#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#include "Entity.h"
#include "Character.h"
#include "Ground.h"
#include "Vector.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "MapManager.h"
#include "DataReader.h"
#include "Shader.h"
#include "PlayerControl.h"
#include "KeyListener.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

class EntityManager{
protected:
    //std::vector<Object*> active_obj_list;
    std::vector<Ground*> groundList;
    std::vector<Character*> characterList;
    Vec2* gravity;
    Camera* cam;
    ResourceManager* resman;
    MapManager* mapman;
    DataReader* parser;
    PhysicsManager* einstein;
    Shader* shader;
    PlayerControl* controller;

public:
    //std::string mapname;
    EntityManager();
    ~EntityManager();
    void addChar(float x, float y, float sz, std::string &texname);
    void addGrd(float x, float y, float sz, std::string &texname);
    void clearObjects();
    void deleteObj();
    void draw();
    void applyPhysics();
    void updateCam();
    void loadMap(std::string name);
    void saveMap();
    void setMap(std::string arr);
    void setControllerListener(KeyListener* pkl);
};



#endif
