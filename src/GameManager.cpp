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
    renderer = new Renderer("simpleshader.vert", "simpleshader.frag", "textshader.vert", "textshader.frag");
    scriptman = new ScriptManager();
    scriptman->execute();
    parser = new DataReader();
    mapman = new MapManager();
    ffactory = new FontFactory();

    
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

        if(i == 50)
        {
            //FIXME Need to find a cross-platform equivalent (SDL_GetTicks maybe?)
            gettimeofday(&t, NULL);
            t1 = t.tv_sec + t.tv_usec/1000000.00;
        }

        gettimeofday(&t, NULL);
        t1 = t.tv_sec + t.tv_usec/1000000.00;

        entityman->applyPhysics();
        entityman->updateCam();
        renderer->draw(entityman, mapman, ffactory);

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
