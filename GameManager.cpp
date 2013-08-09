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
    Einstein->makeObj();

    while (!done)
    {
        gettimeofday(&t, NULL);
        t1 = t.tv_sec + t.tv_usec/1000000.00;
        done = listener->query();
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
