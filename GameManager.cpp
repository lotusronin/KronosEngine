#include "GameManager.h"
#include <SDL/SDL.h>
#include "Window.h"
#include "KeyListener.h"
#include "EntityManager.h"
#include <GL/glu.h>
#include <GL/gl.h>

GameManager::GameManager(){}

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
        done = listener->query();
        Einstein->applyPhysics();
        Einstein->moveObjects();
        //triangle->moveobj(listener->getKeys());

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glLoadIdentity();

        Einstein->draw();

        SDL_GL_SwapBuffers();
    } // end main loop
    return 0;
}
