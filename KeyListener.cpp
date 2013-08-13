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
        if (keys[SDLK_LEFT] && !keys[SDLK_RIGHT])
            return 1;
        else if (keys[SDLK_RIGHT] && !keys[SDLK_LEFT])
            return 2;
        else
            return 0;

}

int KeyListener::save(){

    SDL_Event event;
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_s)
            return 1;
        else if(event.key.keysym.sym == SDLK_l)
            return 2;
    }
    return 0;
}
