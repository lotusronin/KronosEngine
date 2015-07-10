#include "EntityManager.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "defer.h"

EntityManager::EntityManager()
{
    cam = new Camera(320, 240);
    einstein = new PhysicsManager();
    controller = new PlayerControl();
}

EntityManager::~EntityManager()
{
    for(auto it : characterList){
            delete it;
    }
    for(auto it : groundList){
            delete it;
    }
    delete einstein;
    delete cam;
    delete controller;
}

void EntityManager::setMap(std::string arr)
{
    std::cout << arr << '\n';
    //mapname = arr;
}

void EntityManager::clearObjects()
{
    std::cout << "Clearing objects from map...\n";
    for(auto it : groundList){
            delete it;
    }
    for(auto it : characterList){
            delete it;
    }
    for(auto it : itemList){
            delete it;
    }
    characterList.erase(characterList.begin(), characterList.end());
    groundList.erase(groundList.begin(), groundList.end());
    itemList.erase(itemList.begin(), itemList.end());
}

void EntityManager::addGrd(float x, float y, float sz, std::string &texname)
{
    groundList.push_back(new Ground(x, y, sz));
    (groundList.back())->setTexName(texname);
    (groundList.back())->setTexture(resman->getTexture((groundList.back())->getTexName()));
}

void EntityManager::addChar(float x, float y, float sz, std::string &texname)
{
    characterList.push_back(new Character(x, y, sz));
    (characterList.back())->setTexName(texname);
    (characterList.back())->setTexture(resman->getTexture((characterList.back())->getTexName()));
}

void EntityManager::addItem(float x, float y, float sz, std::string &texname)
{
    itemList.push_back(new Item(x, y, sz));
    (itemList.back())->setTexName(texname);
    (itemList.back())->setTexture(resman->getTexture((itemList.back())->getTexName()));
}

void EntityManager::updateCam()
{
    //Update the camera here
    cam->UpdateView((*characterList.begin())->getCenterX(), (*characterList.begin())->getCenterY());
}

void EntityManager::applyPhysics()
{
    controller->moveCharacter();
    
    //Script Test 3!!!
    Character* player = *characterList.begin();
    characterList.back()->executeScripts(player);

    einstein->applyPhysics(&characterList, &groundList);
}

void EntityManager::setControllerListener(KeyListener* pkl)
{
    controller->setKeyListener(pkl);
}


void EntityManager::setResourceManager(ResourceManager* prm) {
    resman = prm;
}

void EntityManager::showInfo() {
    std::cout << "Number of Ground Objects: " << groundList.size() << " \nNumber of Character Objects: " << characterList.size() <<
    "\nNumber of Item Objects: " << itemList.size() << "\n\n";
    controller->setCharacter((*characterList.begin()));
}

std::vector<Ground*>* EntityManager::getGroundList() {
    return &groundList;
}

std::vector<Character*>* EntityManager::getCharacterList() {
    return &characterList;
}

std::vector<Item*>* EntityManager::getItemList() {
    return &itemList;
}

Camera* EntityManager::getCamera() {
    return cam;
}

