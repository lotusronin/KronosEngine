#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "GameManager.h"

int main ( int argc, char** argv )
{
    GameManager* gman = new GameManager();

    gman->init();
    int x = gman->run();

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
