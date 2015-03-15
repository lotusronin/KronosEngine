#include "EntityManager.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

EntityManager::EntityManager()
{
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
    guiman = new GUIManager();
    fpsVal = "0";
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
    delete ffactory;
    delete einstein;
    delete cam;
    delete controller;
    delete shader;
    delete textshader;
    delete guiman;
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
    for(std::vector<Item*>::iterator it = itemList.begin(); it != itemList.end(); it++){
            delete (*it);


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

    for(std::vector<Item*>::iterator it = itemList.begin(); it != itemList.end(); it++){
            (*it)->draw(shader);
    }

    shader->disable();

    //To test font rendering **Move out to another class soon
    textshader->enable();

    /*ffactory->renderLetter('m',-1,-0.9, textshader);
    ffactory->renderLetter('a',-0.92,-0.9, textshader);
    ffactory->renderLetter('p',-0.84,-0.9, textshader);*/
    std::string m = "map";
    ffactory->renderString(m, -1, -0.9f, textshader);

    std::string NameToPrint = mapman->getMapName();
    ffactory->renderString(NameToPrint, -0.7f, -0.9f, textshader);
    /*
    for(int i = 0; i < NameToPrint.size(); i++)
    {
        ffactory->renderLetter(NameToPrint.at(i), -0.7f+i*(0.08f), -0.9f, textshader);
    }*/

    std::string f = "fps";
    ffactory->renderString(f, -1, -1, textshader);
    //There was an ogl error with the font rendering
    //ffactory->renderLetter('M', 0.0f, 0.0f, textshader);
    /*ffactory->renderLetter('f',-1,-1, textshader);
    ffactory->renderLetter('p',-0.92,-1, textshader);
    ffactory->renderLetter('s',-0.84,-1, textshader);*/

    ffactory->renderString(fpsVal, -0.68f,-1.0f, textshader);
    /*
    for(int i = 0; i < fpsVal.length(); i++)
    {
        ffactory->renderLetter(fpsVal.at(i),-0.68+(i*0.08f),-1, textshader);
        if(i >= 6)
            break;
    }*/

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
        else if(!strcmp(pstring.c_str(), "Item"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            addItem(x,y,sz,s);
        }

        parser->closeObj();
        delete[] cstr;
    }
    std::cout << "Number of Ground Objects: " << groundList.size() << " \nNumber of Character Objects: " << characterList.size() <<
    "\nNumber of Item Objects: " << itemList.size() << "\n\n";
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



