#include <cstdlib>
#include <SDL/SDL.h>
#include "KeyListener.h"

KeyListener::KeyListener(){}

KeyListener::~KeyListener(){}

int KeyListener::query(){

    // message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
            // exit if the window is closed
            case SDL_QUIT:
                return 1;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
            {
                    // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                        return 1;
                break;
            }
        } // end switch
    } // end of message processing
    return 0;
}

int KeyListener::getKeys(){
    Uint8 *keys = SDL_GetKeyState(NULL);
     // Handle input
        if (keys[SDLK_LEFT])

            if (keys[SDLK_DOWN] && !keys[SDLK_UP])
                return 8;
            else if (!keys[SDLK_DOWN] && keys[SDLK_UP])
                return 2;
            else
                return 1;

        else if (keys[SDLK_RIGHT])

            if (keys[SDLK_DOWN] && !keys[SDLK_UP])
                return 6;
            else if (!keys[SDLK_DOWN] && keys[SDLK_UP])
                return 4;
            else
                return 5;

        else if (keys[SDLK_DOWN])
        {
            if (!keys[SDLK_UP])
                return 7;
        }
        else if (keys[SDLK_UP])
        {
            if (!keys[SDLK_DOWN])
                return 3;
        }
        else
            return 0;
}
