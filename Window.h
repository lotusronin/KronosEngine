#include <cstdlib>
#include <SDL/SDL.h>
#include <string>

class Window {

public:
    Window(int width, int height, std::string title);
    ~Window();

};
