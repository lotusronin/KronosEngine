#include "GameManager.h"
#include <SDL2/SDL.h>
#include "Window.h"
#include "KeyListener.h"
#include "EntityManager.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <sys/time.h>

GameManager::GameManager(){}

GameManager::~GameManager(){
delete listener;
delete entityman;
delete win_main;
}

void GameManager::setMap(std::string arr)
{
    //std::cout << arr << '\n';
    //entityman->setMap(arr);
    s += arr;
}
void GameManager::init(){
    win_main = new Window(640, 480, "Platform");
    listener = new KeyListener();
    entityman = new EntityManager();
    if(s != "")
    {
        //std::cout << s << "\n";
        entityman->mapname = s;
    }
}

int GameManager::run(){
    // program main loop
    int done = 0;
    int save = 0;
    int loaded = 0;
    //entityman->loadMap();
    //entityman->makeObj();

    while (!done)
    {
        gettimeofday(&t, NULL);
        t1 = t.tv_sec + t.tv_usec/1000000.00;
        done = listener->query();
        save = listener->save();
        if(save == 1)
        {
            entityman->saveMap();
            save = 0;
        }
        else if(save == 2)
        {
            entityman->loadMap();
            save = 0;
            loaded = 1;
        }

        if(loaded){
        //entityman->applyPhysics(listener->getKeys());
        //entityman->moveObjects();

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glLoadIdentity();

        entityman->applyPhysics();
        entityman->updateCam();
        entityman->draw();



        //SDL_GL_SwapBuffers();
        SDL_GL_SwapWindow(win_main->screen);
        gettimeofday(&t, NULL);
        t2 = t.tv_sec + t.tv_usec/1000000.00;
        //calcfps();
        }
    } // end main loop
    return 0;
}

void GameManager::calcfps(){
    double dt = (t2-t1);
    //std::cout << dt << "\n";
    std::cout << 1/dt << "\n";
/*

1 frame / x ms = y frames / second

*/
}
