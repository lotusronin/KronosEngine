#include "Character.h"
#include "Ground.h"
#include "PhysicsManager.h"
#include <vector>
#include <math.h>

PhysicsManager::PhysicsManager()
{
    mat = Matrix();
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::applyPhysics(std::vector<Character*> *cvect, std::vector<Ground*> *gvect)
{
    //std::cout << "Beginning Physics calculations...\n";
    //Apply Gravity to all character entities
    for(auto it : (*cvect))
    {
        //(*it)->pSquare->addForce(0, (*it)->pSquare->getMass()*10);
        it->pSquare->addVeloc(0.0f, -0.2f);
    }


    //Check for collisions
    for(auto it : (*cvect))
    {
        for(auto it2 : (*gvect))
        {
            std::vector<float> *coords1 = it->pSquare->getCoords();
            std::vector<float> *coords2 = it2->pSquare->getCoords();
            //float velx = (*it)->pSquare->getVelx();
            //float vely = (*it)->pSquare->getVely();
            //std::cout << "The velocity from pSquare is... " << vely << "\n";
            //int x =
            //std::cout << (*it)->pSquare << "\n";
            edgeCollide( coords1, coords2, it->pSquare, it2->pSquare);
        }
    }

    /*
    std::cout << "\n\nWould Update Matrix now...\n";*/

    //Update the translation matrices for every character object based on their velocity
    for(auto it : (*cvect))
    {
        float dx, dy;
        dx = it->pSquare->getVelx();
        dy = it->pSquare->getVely();
        it->pSquare->update();
        mat.setTranslation(dx, dy, 0);
        (*it->ptransmat) = (*it->ptransmat)*mat;
    }


    //for(auto it2 = (*gvect).begin(); it2 != (*gvect).end(); it2++)
      //  (*it2)->update();
}

void PhysicsManager::edgeCollide(std::vector<float>* EntityCoords1, std::vector<float>* EntityCoords2, PhysicsSquare* PhysicsBody1, PhysicsSquare* PhysicsBody2)
{
    //int retval = 0;
    //Check to see if already collided
    //Check to see if going to collide
    //std::cout << PhysicsBody1 << "\n";
    //std::cout << "Beginning Collision Checks...\n";
    //Check to see if the X values match up
    // Ent1 x >= Ent2 x && Ent1 x <= Ent2 x+sz    ||   Ent1 x+sz >= Ent2 x && Ent1 x+sz <= Ent2 x+sz
    if( ((*EntityCoords1)[0] >= (*EntityCoords2)[0] && (*EntityCoords1)[0] <= (*EntityCoords2)[2]) || ((*EntityCoords1)[2] >= (*EntityCoords2)[0] && (*EntityCoords1)[2] <= (*EntityCoords2)[2]) )
    {
        //std::cout << "Horizontal Alignment pass!\n";
        //Check to see if already collided/on Ground
        if((*EntityCoords1)[1] == (*EntityCoords2)[5] && PhysicsBody1->getVely() <= 0)
        {
            //std::cout << "We are in case 1!!!!\n";
            //Set Velocity to 0
            PhysicsBody1->setVeloc(PhysicsBody1->getVelx(), 0.0f);
            PhysicsBody1->onGround = 1;
        }
        //Else Check if they will collide with given trajectory
        else if( (*EntityCoords1)[1] > (*EntityCoords2)[5] && ((*EntityCoords1)[1]+PhysicsBody1->getVely()) < (*EntityCoords2)[5] )
        {
            //std::cout << "We are in case 2!!!!\n";
            //Slow Down Entity
            float diffy;
            //std::cout << "Character y = " << (*EntityCoords1)[1] << " Ground y+sz = " << (*EntityCoords2)[5] << "\n";
            diffy = (*EntityCoords2)[5] - (*EntityCoords1)[1];
            //diffy = (*EntityCoords1)[1] - (*EntityCoords2)[5];
            //std::cout << "Diffy is: " << diffy << "\n";
            PhysicsBody1->setVeloc(PhysicsBody1->getVelx(), diffy);
            //float res = diffy + PhysicsBody1->getVely();
        }
        //Must be clear!
        else
        {
            //std::cout << "We are in case 3!!!!\n";
            //Nothing to do.
        }
    }
    //std::cout << "Ending Collision Checks...\n";
    //std::cout << "Ending Collision Checks...\n Velx: " << PhysicsBody1->getVelx() << " Vely: "<< PhysicsBody1->getVely() << "\n\n";

    //return retval;
}
