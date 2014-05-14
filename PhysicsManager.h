#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <vector>
#include <math.h>
#include "Character.h"
#include "Ground.h"
#include "Matrix.h"
#include "PhysicsSquare.h"

class PhysicsManager{
private:
    TranslationMatrix mat;
public:
    PhysicsManager();
    ~PhysicsManager();
    void applyPhysics(std::vector<Character*> *cvect, std::vector<Ground *> *gvect);
    void edgeCollide(std::vector<float>* EntityCoords1, std::vector<float>* EntityCoords2, PhysicsSquare* PhyiscsBody1, PhysicsSquare* PhyiscsBody2);
};
#endif // PHYSICSMANAGER_H
