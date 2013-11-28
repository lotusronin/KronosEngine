#include "Ground.h"

#define M2PIX 10

Ground::Ground(float x, float y, float sz) : Entity(x*M2PIX, y*M2PIX, sz*M2PIX)
{
    pSquare = new PhysicsSquare(x, y, sz);
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
