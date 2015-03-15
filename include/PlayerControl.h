#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "Character.h"
#include "KeyListener.h"

class PlayerControl{
protected:
    Character* playerchar;
    KeyListener* klisten;
public:
    PlayerControl();
    ~PlayerControl();
    void moveCharacter();
    void setKeyListener(KeyListener* plistener);
    void setCharacter(Character* pcharacter);
};
#endif // PLAYERCONTROL_H
