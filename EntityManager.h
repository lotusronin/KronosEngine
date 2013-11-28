#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "Ground.h"
#include "Vector.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "MapManager.h"
#include "DataReader.h"
#include <GL/glu.h>
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

public:
    EntityManager();
    ~EntityManager();
    void makeObj(int x, int y, int sz);
    void addChar(int x, int y, int sz);
    void addGrd(int x, int y, int sz);
    void clearObjects();
    void deleteObj();
    void draw();
    void applyPhysics();
    void applyPhysics(int dir);
    void moveObjects();
    int collide(Vec2* spd1, Vec2* spd2, int* vert1, int* vert2);
    void updateObjs();
    void updateCam();
    void loadMap();
    void saveMap();
};



#endif
