#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "GameManager.h"

int main ( int argc, char* argv[] )
{
    GameManager* gman = new GameManager();

    if(argc > 2)
    {
        std::string str1 = std::string(argv[2]);
        str1 += ".map";
        gman->setMap(str1);
    }

    gman->init();
    int x = gman->run();
    delete gman;

    if(!x){
        // all is well ;)
        printf("Exited cleanly\n");
        return 0;
    }
    else{
        printf("There was an error\n");
        return 1;
    }
}
