#include "GameManager.h"
#include <SDL/SDL.h>
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
delete Einstein;
delete win_main;
}

void GameManager::init(){
    win_main = new Window(640, 480, "Platform");
    listener = new KeyListener();
    Einstein = new EntityManager();
}

int GameManager::run(){
    // program main loop
    int done = 0;
    int save = 0;
    int loaded = 0;
    //Einstein->loadMap();
    //Einstein->makeObj();

    while (!done)
    {
        gettimeofday(&t, NULL);
        t1 = t.tv_sec + t.tv_usec/1000000.00;
        done = listener->query();
        save = listener->save();
        if(save == 1)
        {
            Einstein->saveMap();
            save = 0;
        }
        else if(save == 2)
        {
            Einstein->loadMap();
            save = 0;
            loaded = 1;
        }

        if(loaded){
        Einstein->applyPhysics(listener->getKeys());
        Einstein->moveObjects();

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glLoadIdentity();

        Einstein->updateCam();
        Einstein->draw();



        SDL_GL_SwapBuffers();
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
