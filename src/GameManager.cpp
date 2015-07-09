#include "GameManager.h"
#include <SDL2/SDL.h>
#include "Window.h"
#include "KeyListener.h"
#include "EntityManager.h"
#include "defer.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <sys/time.h>
#include <cstring>
#include <string>

GameManager::GameManager()
{}

GameManager::~GameManager()
{
    delete shader;
    delete textshader;
    delete scriptman;
    delete resman;
    delete parser;
    delete listener;
    delete entityman;
    delete win_main;
    delete mapman;
}

void GameManager::setMap(std::string arr)
{
    //std::cout << arr << '\n';
    //entityman->setMap(arr);
    s += arr;
}

void GameManager::LoadMap()
{
    //std::cout << "Current Map Name is : " << entityman->mapname << "\n";
    s = "";
    while(!s.compare(""))
    {
        std::cout << "Enter in a map you would like to load: ";
        std::cin >> s;
    }
    std::cout << "The map name you entered is: " << s << "\n\n";
    s += ".map";
    //entityman->mapname = s + ".map";
    
    //Fill In!
    std::string name = s;
    entityman->clearObjects();
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

    std::vector<std::string>* currentMap = mapman->getMapData();

    //Parse the String
    std::cout << "Map Name: "<< mapman->getMapName() << "\n";
    std::cout << "Map Music: " << mapman->getMusicName() << "\n";
    resman->loadMusic(mapman->getMusicName());

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
            entityman->addChar(x,y,sz,s);
        }
        else if(!strcmp(pstring.c_str(),"Ground"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            entityman->addGrd(x,y,sz,s);
        }
        else if(!strcmp(pstring.c_str(), "Item"))
        {
            std::string s = parser->getValue("texture");
            resman->loadTexture(s);
            entityman->addItem(x,y,sz,s);
        }
    }
    
    entityman->showInfo();
    resman->getMusic();
    //FIXME Script tests.
    
    //Script Test!!!
    /*
    std::string scriptName = "EntityMethodTest";
    Script* temp = scriptman->loadScript(scriptName);
    temp->execute(*groundList.begin());
    */
 
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

void GameManager::init()
{
    win_main = new Window(640, 480, "Platform");
    glewInit();
    listener = new KeyListener();
    entityman = new EntityManager();
    /*if(s != "")
    {
        //std::cout << s << "\n";
        entityman->mapname = s;
    }*/
    entityman->setControllerListener(listener);
    resman = new ResourceManager();
    resman->initSound();
    shader = new Shader("simpleshader.vert", "simpleshader.frag");
    shader->compile();
    textshader = new Shader("textshader.vert", "textshader.frag");
    textshader->compile();
    scriptman = new ScriptManager();
    scriptman->execute();
    parser = new DataReader();
    mapman = new MapManager();

    
    // TODO pull out functionality from EntityManager!!!
    entityman->setResourceManager(resman);
    entityman->setScriptManager(scriptman);
}

int GameManager::run()
{
    // program main loop
    int done = 0;
    int save = 0;
    int loaded = 0;
    int i = 0;

    int targetFPS = 1000/60;
    int currentTime, frameTime;


    while (!done)
    {
        currentTime = SDL_GetTicks();

        done = listener->query();
        save = listener->save();
        if(save == 1)
        {
            entityman->saveMap(mapman);
            save = 0;
        }
        else if(save == 2)
        {
            LoadMap();
            //entityman->loadMap(s);
            save = 0;
            loaded = 1;
        }

        if(loaded){

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(i == 50)
        {
            gettimeofday(&t, NULL);
            t1 = t.tv_sec + t.tv_usec/1000000.00;
        }

        gettimeofday(&t, NULL);
        t1 = t.tv_sec + t.tv_usec/1000000.00;

        entityman->applyPhysics();
        entityman->updateCam();
        entityman->draw(shader, textshader, mapman);



        SDL_GL_SwapWindow(win_main->screen);

        if(i == 50)
        {
            gettimeofday(&t, NULL);
            t2 = t.tv_sec + t.tv_usec/1000000.00;
            calcfps();
            i = 0;
        }
        else
        {
            i++;
        }

        }
        
        //Fix Frame skipping
        frameTime = SDL_GetTicks() - currentTime;
        if(frameTime < targetFPS) {
            SDL_Delay(targetFPS-frameTime);
        }
    } // end main loop
    return 0;
}

void GameManager::calcfps()
{
    double dt = (t2-t1);
    //std::cout << dt << "\n";
    //std::cout << 1/dt << "\n";
    entityman->fpsVal = std::to_string(float(1/dt));
/*

1 frame / x ms = y frames / second

*/
}
