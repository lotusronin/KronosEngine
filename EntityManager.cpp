#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager(){
    player = new MobileObject();
    gravity = new Vec2(0, 5);
    cam = new Camera(320, 240);
    resman = new ResourceManager();
    resman->loadTexture();
}

EntityManager::~EntityManager(){
    //player->~MobileObject();
    delete player;
    for(std::vector<Object*>::iterator it = active_obj_list.begin(); it != active_obj_list.end(); it++){
            /*(*it)->~Object();*/
            delete (*it);
    }
}

void EntityManager::makeObj(){
active_obj_list.push_back(new Object());
(*active_obj_list.begin())->setTexture(resman->getTexture());
}

void EntityManager::updateCam(){
//Update the camera here
    cam->UpdateView(player->getCenterX(), player->getCenterY());
}

void EntityManager::draw(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    player->draw();
    for(std::vector<Object*>::iterator it = active_obj_list.begin(); it != active_obj_list.end(); it++){
            (*it)->draw();
    }
}

void EntityManager::moveObjects(){
    player->moveobj();
}

    /*
    **  DO COLLISION DETECTION STUFF HERE!!!
    */

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
                std::cout<< "Not implemented yet! \n";
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
}
