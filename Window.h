#ifndef WINDOW_H
#define WINDOW_H
#include <cstdlib>
#include <SDL2/SDL.h>
#include <string>

class Window {

public:
    Window(int width, int height, std::string title);
    ~Window();
    SDL_Window* screen;

};

#endif
