#include "Character.h"
#include "Ground.h"
#include "PhysicsManager.h"
#include <vector>
#include <math.h>

PhysicsManager::PhysicsManager()
{
    mat = TranslationMatrix();
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::applyPhysics(std::vector<Character*> *cvect, std::vector<Ground*> *gvect)
{
    //std::cout << "Beginning Physics calculations...\n";
    //Apply Gravity to all character entities
    for(std::vector<Character*>::iterator it = (*cvect).begin(); it != (*cvect).end(); it++)
    {
        //(*it)->pSquare->addForce(0, (*it)->pSquare->getMass()*10);
        (*it)->pSquare->addVeloc(0.0f, -0.2f);
    }


    //Check for collisions
    for(std::vector<Character*>::iterator it = (*cvect).begin(); it != (*cvect).end(); it++)
    {
        for(std::vector<Ground*>::iterator it2 = (*gvect).begin(); it2 != (*gvect).end(); it2++)
        {
            std::vector<float> *coords1 = (*it)->pSquare->getCoords();
            std::vector<float> *coords2 = (*it2)->pSquare->getCoords();
            //float velx = (*it)->pSquare->getVelx();
            //float vely = (*it)->pSquare->getVely();
            //std::cout << "The velocity from pSquare is... " << vely << "\n";
            //int x =
            //std::cout << (*it)->pSquare << "\n";
            edgeCollide( coords1, coords2, (*it)->pSquare, (*it2)->pSquare);
        }
        //(*it)->pSquare->update();
    }

    /*std::cout << "\n\nEnter a char: ";
    char a;
    std::cin >> a;
    std::cout << a;
    std::cout << "\n\nWould Update Matrix now...\n";*/

    //Update the translation matrices for every character object based on their velocity
    for(std::vector<Character*>::iterator it = (*cvect).begin(); it != (*cvect).end(); it++)
    {
        float dx, dy;
        dx = (*it)->pSquare->getVelx();
        dy = (*it)->pSquare->getVely();
        (*it)->pSquare->update();
        /*std::cout << "dx: " << dx << " dy: " << dy <<"\n";
        char a;
        std::cin >> a;
        std::cout << a << "\n\n";*/
        mat.SetTranslation(dx, dy, 0);
        (*(*it)->ptransmat) = (*(*it)->ptransmat)*mat;
        //(*it)->update();
    }


    //for(std::vector<Ground*>::iterator it2 = (*gvect).begin(); it2 != (*gvect).end(); it2++)
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

    /*
    **  DO COLLISION DETECTION STUFF HERE!!!
    */
/*
void EntityManager::applyPhysics(int dir){
    //Apply Grav. to all movable objects
    player->addForce(gravity);

    //Check for collisions
    int x;
    for(std::vector<Object*>::iterator it = active_obj_list.begin(); it != active_obj_list.end(); it++){
            x = collide(player->getSpeed(), (*it)->getSpeed(), player->getVerts(), (*it)->getVerts() );
            //std::cout << x << "\n";

            if(x == 1){
                Vec2* normF = new Vec2(0, player->getSpeed()->gety());
                normF->negy();
                player->addForce(normF);
                player->setonground(true);
            }
            else if(x == 3){
                int ydiff = (*(player->getVerts()+5) + player->getSpeed()->gety() - *((*it)->getVerts()+1) ) + 1;
                Vec2* slow = new Vec2(0, player->getSpeed()->gety() - ydiff);
                player->stop(false, true);
                player->addForce(slow);
            }
            else{
                //std::cout<< "Not implemented yet! \n";
            }
    }

    player->stop(true, false);
    if(dir && player->isonground()){
        if(dir == 1){
            Vec2* run = new Vec2(-2, 0);
            player->addForce(run);
        }
        else if(dir == 2){
            Vec2* run = new Vec2(2, 0);
            player->addForce(run);
        }
    }
}

int EntityManager::collide(Vec2* spd1, Vec2* spd2, int* vert1, int* vert2){
    //Check Case 1, Already on ground

    //check Y values
    if(*(vert1+5)+1 == *(vert2+1)){
        //check X values
        if( ( *(vert1+4) <= *(vert2+2) ) && ( *(vert1+4) >= *(vert2) ) ){
            return 1;
        }
    }

    //Check Case 2, The objects are inside of each other

    //check Y values
    if( (*(vert1+5) >= *(vert2+1)) && ( *(vert1+5) <= *(vert2+5)) ){
        //check X values
        if( ( *(vert1+4) <= *(vert2+2) ) && ( *(vert1+4) >= *(vert2) ) ){
            return 2;
        }
    }

    int dx, dy, dx2, dy2;
    dx = spd1->getx();
    dy = spd1->gety();
    dx2 = spd2->getx();
    dy2 = spd2->gety();
    //Check Case 3, One object will overtake the other

    //check Y values
    if( (*(vert1+5)+dy >= *(vert2+1))+dy2 && ( *(vert1+5) < *(vert2+1)) ){
        //check X values
        if( ( *(vert1+4)+dx <= *(vert2+2)+dx2 ) && ( *(vert1+4)+dx >= *(vert2)+dx2 ) ){
            return 3;
        }
    }

    return 0;
}*/
