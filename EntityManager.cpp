#include "EntityManager.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

EntityManager::EntityManager(){
    //player = new MobileObject();
    gravity = new Vec2(0, 5);
    cam = new Camera(320, 240);
    resman = new ResourceManager();
    resman->loadTexture();
    mapman = new MapManager();
    parser = new DataReader();
    //mapman->newMap("Debug");
}

EntityManager::~EntityManager(){
    for(std::vector<Object*>::iterator it = active_obj_list.begin(); it != active_obj_list.end(); it++){
            delete (*it);
    }
    delete resman;
    delete player;
    delete mapman;
    delete parser;
}

void EntityManager::makeObj(int x, int y, int sz){
active_obj_list.push_back(new Object(x, y, sz));
(active_obj_list.back())->setTexture(resman->getTexture());
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

void EntityManager::saveMap(){
    mapman->saveMap("debug.map");
}

void EntityManager::loadMap(){
    mapman->loadMap("debug.map");
    //mapman->showMap();
    std::vector<std::string>* currentMap = mapman->getMapData();

    //Parse the String
    std::vector<std::string>::iterator it = (*currentMap).begin();
    std::cout << "Map Name: "<< mapman->getMapName() << "\n";

    for(it; it != (*currentMap).end(); it++){
        char *cstr = new char[(*it).length() + 1];
        std::strcpy (cstr, (*it).c_str());
        char * p = std::strtok (cstr,",");
        std::cout << p << "\n";
        int x = atoi(p);

        p = std::strtok(NULL,",");
        std::cout << p << "\n";
        int y = atoi(p);

        p = std::strtok(NULL,",");
        std::cout << p << "\n";

        std::string pstring = p;
        parser->loadObj(pstring);
        pstring = parser->getValue("size");
        int sz = atoi(pstring.c_str());
        pstring = parser->getValue("entity_type");
        parser->closeObj();

        if(!strcmp(pstring.c_str(),"MobileObject"))
        {
            player = new MobileObject(x,y,sz);
        }
        else if(!strcmp(pstring.c_str(),"Object"))
        {
            makeObj(x,y,sz);
        }

        delete[] cstr;
    }
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
}
