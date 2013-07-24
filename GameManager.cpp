#include "GameManager.h"
#include <SDL/SDL.h>
#include "Window.h"
#include "KeyListener.h"
#include "Object.h"
#include <GL/glu.h>
#include <GL/gl.h>

GameManager::GameManager(){}

void GameManager::init(){
    win_main = new Window(640, 480, "Platform");
    listener = new KeyListener();
    triangle = new Object();
    gravity = new Vec2(0, 5);
}

int GameManager::run(){
    // program main loop
    int done = 0;
    while (!done)
    {
        done = listener->query();
        triangle->addForce(gravity);
        triangle->moveobj(listener->getKeys());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        triangle->draw();

        SDL_GL_SwapBuffers();
    } // end main loop
    return 0;
}
