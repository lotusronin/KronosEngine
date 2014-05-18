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

    if(dir >= 10)
    {
        //We are trying to jump
        if(playerchar->pSquare->onGround == 1)
        {
            playerchar->pSquare->addVeloc(0.0f, 5.0f);
            playerchar->pSquare->onGround = 0;
        }
        dir -= 10;
    }

    float vx = 2.0f;
    float vy = playerchar->pSquare->getVely();

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
