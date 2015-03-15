#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "PhysicsSquare.h"
#include <cstdlib>
#include <vector>
#include <GL/gl.h>

/*
    This is the Item Entity used for all item objects.
    Items are objects throughout the world that the player
    can interact with like Treasure chests, pots, grass, etc.

    These are not things like potions, coins, or water.
    For those, see the Consumable entity, a subclass of Item.

*/


class Item : public Entity{
public:
    Item(float x, float y, float sz);
    ~Item();
    PhysicsSquare* getObj();
protected:
    PhysicsSquare* pSquare;
};

#endif // ITEM_H
