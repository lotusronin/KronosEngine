#include "Window.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

Window::Window(int width, int height, std::string title){

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
    /*SDL_Window* screen = SDL_CreateWind(width, height, 16,
                                           SDL_HWSURFACE|SDL_OPENGL);*/
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_GLContext context = SDL_GL_CreateContext(screen);
    //SDL_WM_SetCaption(title.c_str(),title.c_str());


    glClearColor(0,0,0,0);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 1, -1);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();

}

Window::~Window(){
}
