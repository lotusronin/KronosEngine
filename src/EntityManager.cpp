#include "EntityManager.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "defer.h"

EntityManager::EntityManager()
{
    cam = new Camera(320, 240);
    resman = new ResourceManager();
    resman->initSound();
    resman->loadMusic("test.ogg");
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
    scriptman = new ScriptManager();
    scriptman->execute();
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
    delete scriptman;
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

void EntityManager::draw()
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
    std::cout << "Map Name: "<< mapman->getMapName() << "\n";

    for(auto it : (*currentMap)){
        char *cstr = new char[it.length() + 1];
        defer { delete[] cstr; };
        std::strcpy (cstr, it.c_str());
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
        defer { parser->closeObj(); };

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

        //parser->closeObj();
        //delete[] cstr;
    }
    std::cout << "Number of Ground Objects: " << groundList.size() << " \nNumber of Character Objects: " << characterList.size() <<
    "\nNumber of Item Objects: " << itemList.size() << "\n\n";
    resman->getMusic();
    controller->setCharacter((*characterList.begin()));
    
    //Script Test!!!
    std::string scriptName = "EntityMethodTest";
    Script* temp = scriptman->loadScript(scriptName);
    temp->execute(*groundList.begin());
 
    //Script Test 2!!!
    /*
    scriptName = "MoveForwardTest";
    temp = scriptman->loadScript(scriptName);
    characterList.back()->addScript(temp);
    characterList.back()->executeScripts();*/

    //Script Test 3!!!
    /*scriptName = "FollowCharacterTest";
    temp = scriptman->loadScript(scriptName);
    characterList.back()->addScript(temp);
    Character* player = *characterList.begin();
    characterList.back()->executeScripts(player);*/
}

void EntityManager::applyPhysics()
{
    controller->moveCharacter();
    
    //Script Test 3!!!
    /*Character* player = *characterList.begin();
    characterList.back()->executeScripts(player);*/

    einstein->applyPhysics(&characterList, &groundList);
}

void EntityManager::setControllerListener(KeyListener* pkl)
{
    controller->setKeyListener(pkl);
}




