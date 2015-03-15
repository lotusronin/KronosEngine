#include "Window.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>

Window::Window(int width, int height, std::string title)
{

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        SDL_Quit();
        exit(1);
    }

    // make sure SDL cleans up before exit
    //atexit(SDL_Quit);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // create a new window
    const char* name = title.c_str();
    screen = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    context = SDL_GL_CreateContext(screen);
    //SDL_WM_SetCaption(title.c_str(),title.c_str());


    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(screen);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, 0, height, 1, -1);

    //glMatrixMode(GL_MODELVIEW);

    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glLoadIdentity();

    //std::cout << "Refresh Interval is set at... " << SDL_GL_GetSwapInterval() << "\n";
    //SDL_GL_SetSwapInterval(0);
    //std::cout << "Refresh Interval is set at... " << SDL_GL_GetSwapInterval() << "\n";
}

Window::~Window()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(screen);
    SDL_Quit();
}
