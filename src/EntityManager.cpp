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
    //mapman->newMap("Debug");
    
    controller = new PlayerControl();
    ffactory = new FontFactory();
    fpsVal = "0";
}

EntityManager::~EntityManager()
{

    for(auto it : characterList){
            delete it;
    }
    for(auto it : groundList){
            delete it;
    }
    delete ffactory;
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

void EntityManager::draw(Shader* shader, Shader* textshader, MapManager* mapman)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->enable();
	//std::cout << "Beginning to draw entities...\n";
    //player->draw();
    GLint cameraloc = glGetUniformLocation(shader->shaderProgram, "camera");

    glUniformMatrix4fv(cameraloc, 1, GL_FALSE, cam->GetTransform()->mat);

    for(auto it : characterList){
            it->draw(shader);
    }
    //shader->enable();
    for(auto it : groundList){
            it->draw(shader);
    }

    for(auto it : itemList){
            it->draw(shader);
    }

    shader->disable();

    //To test font rendering **Move out to another class soon
    textshader->enable();

    std::string m = "map";
    ffactory->renderString(m, -1, -0.8f, textshader);

    std::string NameToPrint = mapman->getMapName();
    ffactory->renderString(NameToPrint, -0.87f, -0.8f, textshader);

    std::string f = "fps";
    ffactory->renderString(f, -1, -0.9f, textshader);

    ffactory->renderString(fpsVal, -0.9f,-0.9f, textshader);

    textshader->disable();
    //End of font testing
}

void EntityManager::saveMap(MapManager* mapman)
{
    mapman->saveMap("debug.map");
}

void EntityManager::applyPhysics()
{
    controller->moveCharacter();
    
    //Script Test 3!!!
    /*Character* player = *characterList.begin();
    characterList.back()->executeScripts(;player);*/

    einstein->applyPhysics(&characterList, &groundList);
}

void EntityManager::setControllerListener(KeyListener* pkl)
{
    controller->setKeyListener(pkl);
}


void EntityManager::setResourceManager(ResourceManager* prm) {
    resman = prm;
}

void EntityManager::setScriptManager(ScriptManager* psm) {
    scriptman = psm;
}

void EntityManager::showInfo() {
    std::cout << "Number of Ground Objects: " << groundList.size() << " \nNumber of Character Objects: " << characterList.size() <<
    "\nNumber of Item Objects: " << itemList.size() << "\n\n";
    controller->setCharacter((*characterList.begin()));
}
