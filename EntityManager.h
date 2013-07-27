#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Object.h"
#include "Vector.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

class EntityManager{
protected:
    std::vector<immobileObject*> active_obj_list;
    Object* player;
    Vec2* gravity;
public:
    EntityManager();
    ~EntityManager();
    void makeObj();
    void deleteObj();
    void draw();
    void applyPhysics();
    void moveObjects();
    int collide(Vec2* spd1, Vec2* spd2, int* vert1, int* vert2);
};



#endif
