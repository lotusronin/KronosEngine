#include "GameManager.h"
#include <SDL2/SDL.h>
#include "Window.h"
#include "KeyListener.h"
#include "EntityManager.h"
#include "Renderer.h"
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
    delete scriptman;
    delete resman;
    delete parser;
    delete listener;
    delete entityman;
    delete win_main;
    delete mapman;
    delete renderer;
    delete ffactory;
    delete eventman;
}

void GameManager::setMap(std::string arr)
{
    //std::cout << arr << '\n';
    //entityman->setMap(arr);
    s += arr;
}

void GameManager::LoadMap()
{
    s = "";
    while(!s.compare(""))
    {
        std::cout << "Enter in a map you would like to load: ";
        std::cin >> s;
    }
    std::cout << "The map name you entered is: " << s << "\n\n";
    s += ".map";
    
    std::string name = s;
    entityman->clearObjects();
    if(name.compare("") != 0)
    {
        std::cout << "Loading new map: " << name << "\n";
        mapman->loadMap(name.c_str(), resman, entityman, parser);

    }
    else
    {
        std::cout << "Mapname not found, Loading debug.map\n";
        mapman->loadMap("debug.map", resman, entityman, parser);
    }
    
    entityman->showInfo();
    resman->getMusic();
    //FIXME Script tests.
    std::vector<Character*>* cl = entityman->getCharacterList();
    Script* temp;
    std::string scriptName;
    
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
    (*cl).back()->addScript(temp);
    (*cl).back()->executeScripts();*/

    //Script Test 3!!!
    scriptName = "FollowCharacterTest";
    temp = scriptman->loadScript(scriptName);
    (*cl).back()->addScript(temp);
    Character* player = *(*cl).begin();
    (*cl).back()->executeScripts(player);/**/

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
    renderer = new Renderer("simpleshader.vert", "simpleshader.frag", "textshader.vert", "textshader.frag");
    scriptman = new ScriptManager();
    scriptman->execute();
    parser = new DataReader();
    mapman = new MapManager();
    ffactory = new FontFactory();
    eventman = new EventManager();

    // TODO pull out functionality from EntityManager!!!
    entityman->setResourceManager(resman);
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
            mapman->saveMap("debug.map");
            save = 0;
        }
        else if(save == 2)
        {
            LoadMap();
            save = 0;
            loaded = 1;
        }

        if(loaded){


        entityman->applyPhysics();
        entityman->updateCam();
        renderer->draw(entityman, mapman, ffactory, resman);
        resman->incrementFrame();

        SDL_GL_SwapWindow(win_main->screen);
        
        //Fix Frame skipping
        frameTime = SDL_GetTicks() - currentTime;
        if(frameTime < targetFPS) {
            SDL_Delay(targetFPS-frameTime);
        }

        if(i == 50)
        {
            //1 frame / x ms = y frames / second
            renderer->fpsVal = std::to_string(float(1000.0/(SDL_GetTicks() - currentTime)));
            i = 0;
        }
        else
        {
            i++;
        }

        }
    
    } // end main loop
    return 0;
}

