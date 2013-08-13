#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Object.h"
#include "Vector.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "MapManager.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

class EntityManager{
protected:
    std::vector<Object*> active_obj_list;
    MobileObject* player;
    Vec2* gravity;
    Camera* cam;
    ResourceManager* resman;
    MapManager* mapman;

public:
    EntityManager();
    ~EntityManager();
    void makeObj(int x, int y, int sz);
    void deleteObj();
    void draw();
    void applyPhysics(int dir);
    void moveObjects();
    int collide(Vec2* spd1, Vec2* spd2, int* vert1, int* vert2);
    void updateCam();
    void loadMap();
    void saveMap();
};



#endif
