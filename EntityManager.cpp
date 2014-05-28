#include "EntityManager.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

EntityManager::EntityManager()
{
    gravity = new Vec2(0, 5);
    cam = new Camera(320, 240);
    resman = new ResourceManager();
    resman->loadMusic("test.wav");
    mapman = new MapManager();
    parser = new DataReader();
    einstein = new PhysicsManager();
    //mapman->newMap("Debug");
    shader = new Shader("simpleshader.vert", "simpleshader.frag");
    shader->compile();
    textshader = new Shader("textshader.vert", "textshader.frag");
    textshader->compile();

    controller = new PlayerControl();
    ffactory = new FontFactory();
}

EntityManager::~EntityManager()
{

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
    std::cout << arr << '\n';
    //mapname = arr;
}

void EntityManager::clearObjects()
{
    std::cout << "Clearing objects from map...\n";
    for(std::vector<Ground*>::iterator it = groundList.begin(); it != groundList.end(); it++){
            delete (*it);

    }
    for(std::vector<Character*>::iterator it = characterList.begin(); it != characterList.end(); it++){
            delete (*it);


    }
    characterList.erase(characterList.begin(), characterList.end());
    groundList.erase(groundList.begin(), groundList.end());
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

void EntityManager::updateCam()
{
    //Update the camera here
    cam->UpdateView((*characterList.begin())->getCenterX(), (*characterList.begin())->getCenterY());
}

void EntityManager::draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->enable();
	//std::cout << "Beginning to draw entities...\n";
    //player->draw();

    GLint cameraloc = glGetUniformLocation(shader->shaderProgram, "camera");
    glUniformMatrix4fv(cameraloc, 1, GL_FALSE, cam->GetTransform()->mat);

    for(std::vector<Character*>::iterator it = characterList.begin(); it != characterList.end(); it++){
            (*it)->draw(shader);
    }
    //shader->enable();
    for(std::vector<Ground*>::iterator it = groundList.begin(); it != groundList.end(); it++){
            (*it)->draw(shader);
    }

    shader->disable();

    //To test font rendering **Move out to another class soon
    textshader->enable();
    std::string NameToPrint = mapman->getMapName();
    for(int i = 0; i < NameToPrint.size(); i++)
    {
        ffactory->renderLetter(NameToPrint.at(i), 0.0f+i, 0.0f);
    }
    textshader->disable();
    //End of font testing
}

void EntityManager::saveMap()
{
    mapman->saveMap("debug.map");
}

void EntityManager::loadMap(std::string name)
{
    clearObjects();

    if(name.compare("") != 0)
    {
        std::cout << "Loading new map: " << name << "\n";
        mapman->loadMap(name.c_str());

    }
    else
    {
        std::cout << "Mapname not found, Loading debug.map\n";
        mapman->loadMap("debug.map");
    }

    //mapman->showMap();
    //std::cout << "Getting Map Data for: " << mapname.substr(0, mapname.find(".map")) << "\n";
    std::vector<std::string>* currentMap = mapman->getMapData();

    //Parse the String
    std::vector<std::string>::iterator it = (*currentMap).begin();
    std::cout << "Map Name: "<< mapman->getMapName() << "\n";

    for(it; it != (*currentMap).end(); it++){
        char *cstr = new char[(*it).length() + 1];
        std::strcpy (cstr, (*it).c_str());
        char * p = std::strtok (cstr,",");
        //std::cout << p << "\n";
        float x = (float)atof(p);
        //std::cout << "The value of x is: " << x << "\n";


        p = std::strtok(NULL,",");
        //std::cout << p << "\n";
        float y = (float)atof(p);
        //std::cout << "The value of y is: " << y << "\n";

        p = std::strtok(NULL,",");
        //std::cout << p << "\n";

        std::string pstring = p;
        std::cout << "\n" << pstring << " at " << x << "," << y << "\n";

        parser->loadObj(pstring);
        pstring = parser->getValue("size");
        float sz = (float)atof(pstring.c_str());
        pstring = parser->getValue("entity_type");

        if(!strcmp(pstring.c_str(),"Character"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            addChar(x,y,sz,s);
        }
        else if(!strcmp(pstring.c_str(),"Ground"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            addGrd(x,y,sz,s);
        }

        parser->closeObj();
        delete[] cstr;
    }
    std::cout << "Number of Ground Objects: " << groundList.size() << " \nNumber of Character Objects: " << characterList.size() << "\n\n";
    //resman->getMusic();
    controller->setCharacter((*characterList.begin()));
}

void EntityManager::applyPhysics()
{
    controller->moveCharacter();
    einstein->applyPhysics(&characterList, &groundList);
}

void EntityManager::setControllerListener(KeyListener* pkl)
{
    controller->setKeyListener(pkl);
}

