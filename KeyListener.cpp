#include <cstdlib>
#include <SDL2/SDL.h>
#include "KeyListener.h"

KeyListener::KeyListener(){}

KeyListener::~KeyListener(){}

int KeyListener::query(){

    // message processing loop
    SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
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
                if (keys[SDL_SCANCODE_ESCAPE])
                        return 1;
                break;
            }
        } // end switch
    } // end of message processing
    return 0;
}

int KeyListener::getKeys(){
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    while(SDL_PollEvent(&event)){
     // Handle input
        if (keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT])
            return 1;
        else if (keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT])
            return 2;
        else
            return 0;
    }
}

int KeyListener::save(){

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN)
        {
        if (keys[SDL_SCANCODE_S])
            return 1;
        else if(keys[SDL_SCANCODE_L])
            return 2;
        }
    }
    return 0;
}
