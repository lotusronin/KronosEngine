#include "Ground.h"

#define M2PIX 5

Ground::Ground(float x, float y, float sz) : Entity(x*5, y*5, sz*5)
{
    pSquare = new PhysicsSquare(x*5, y*5, sz*5);
}

Ground::~Ground()
{
    delete pSquare;
}

PhysicsSquare* Ground::getObj()
{
    return pSquare;
}

void Ground::update()
{
    pSquare->update();
}
