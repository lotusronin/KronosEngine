#include "PlayerControl.h"

PlayerControl::PlayerControl(){}

PlayerControl::~PlayerControl(){}

void PlayerControl::setKeyListener(KeyListener* plistener)
{
    klisten = plistener;
}

void PlayerControl::setCharacter(Character* pcharacter)
{
    playerchar = pcharacter;
}

void PlayerControl::moveCharacter()
{
    int dir = klisten->getKeys();
    float vy = playerchar->pSquare->getVely();
    float vx = 0.5f;

    if(dir == 1)
    {
        //move char left
        playerchar->pSquare->setVeloc(-vx, vy);
    }
    else if(dir == 2)
    {
        //move char right
        playerchar->pSquare->setVeloc(vx, vy);
    }
    else
    {
        playerchar->pSquare->setVeloc(0.0, vy);
    }


}
