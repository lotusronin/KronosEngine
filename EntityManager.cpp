#include "EntityManager.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

EntityManager::EntityManager(){
    gravity = new Vec2(0, 5);
    cam = new Camera(320, 240);
    resman = new ResourceManager();
    resman->loadTexture();
    resman->loadMusic();
    mapman = new MapManager();
    parser = new DataReader();
    einstein = new PhysicsManager();
    mapname = "";
    //mapman->newMap("Debug");
    shader = new Shader();
    shader->compile();
}

EntityManager::~EntityManager(){
    /*for(std::vector<Object*>::iterator it = active_obj_list.begin(); it != active_obj_list.end(); it++){
            delete (*it);
    }*/
    for(std::vector<Character*>::iterator it = characterList.begin(); it != characterList.end(); it++){
            delete (*it);
    }
    for(std::vector<Ground*>::iterator it = groundList.begin(); it != groundList.end(); it++){
            delete (*it);
    }
    delete resman;
    delete mapman;
    delete parser;
}

void EntityManager::setMap(std::string arr)
{
    //std::cout << arr << '\n';
    mapname = arr;
}

void EntityManager::clearObjects()
{
    for(std::vector<Ground*>::iterator it = groundList.begin(); it != groundList.end(); it++){
            delete (*it);
    }
    for(std::vector<Character*>::iterator it = characterList.begin(); it != characterList.end(); it++){
            delete (*it);
    }
    characterList.erase(characterList.begin(), characterList.end());
    groundList.erase(groundList.begin(), groundList.end());
}

void EntityManager::addGrd(int x, int y, int sz){
groundList.push_back(new Ground(x, y, sz));
(groundList.back())->setTexture(resman->getTexture());
}

void EntityManager::addChar(int x, int y, int sz){
characterList.push_back(new Character(x, y, sz));
}

void EntityManager::updateCam(){
//Update the camera here
    cam->UpdateView((*characterList.begin())->getCenterX(), (*characterList.begin())->getCenterY());
}

void EntityManager::draw(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//shader->enable();
	//std::cout << "Beginning to draw entities...\n";
    //player->draw();
    /*for(std::vector<Object*>::iterator it = active_obj_list.begin(); it != active_obj_list.end(); it++){
            (*it)->draw();
    }*/

    for(std::vector<Character*>::iterator it = characterList.begin(); it != characterList.end(); it++){
            (*it)->draw();
    }
    shader->enable();
    for(std::vector<Ground*>::iterator it = groundList.begin(); it != groundList.end(); it++){
            (*it)->draw(shader);
    }

    shader->disable();
}

void EntityManager::moveObjects(){
    //player->moveobj();
}

void EntityManager::saveMap(){
    mapman->saveMap("debug.map");
}

void EntityManager::loadMap(){
    clearObjects();

    if(mapname != "")
    {
        //std::cout << mapname << '\n';
        mapman->loadMap(mapname.c_str());

    }
    else
    {
        mapman->loadMap("debug.map");
    }

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

        if(!strcmp(pstring.c_str(),"Character"))
        {
            addChar(x,y,sz);
        }
        else if(!strcmp(pstring.c_str(),"Ground"))
        {
            addGrd(x,y,sz);
        }

        delete[] cstr;
    }
    resman->getMusic();
}


void EntityManager::applyPhysics()
{
    //einstein->applyPhysics(&characterList, &groundList);
    //updateObjs();
}

void EntityManager::updateObjs()
{
    for(std::vector<Character*>::iterator it = characterList.begin(); it != characterList.end(); it++){
        (*it)->update();
    }
}

