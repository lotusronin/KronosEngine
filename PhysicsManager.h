#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <vector>
#include "Character.h"
#include "Ground.h"

class PhysicsManager{
public:
    PhysicsManager();
    ~PhysicsManager();
    void applyPhysics(std::vector<Character*> *cvect, std::vector<Ground *> *gvect);
    int edgeCollide(std::vector<float>* p1, std::vector<float>* p2, float vx1, float vy1, float vx2, float vy2);
};
#endif // PHYSICSMANAGER_H
