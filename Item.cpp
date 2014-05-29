#include "Item.h"

Item::Item(float x, float y, float sz) : Entity(x*5, y*5, sz*5)
{
    pSquare = new PhysicsSquare(x*5, y*5, sz*5);
}

Item::~Item()
{
}
