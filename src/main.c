#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "mpos/mpos.h"
#include "init.h"
#include "event.h"
#include "logic.h"
#include "draw.h"


int main(int argc, char **argv)
{
    printf("Let's start...\n");

    RNV_InitSDL();
    RNV_InitGame();

    while (app.state.QUIT == 0)
    {
        MPOS_MpfStart(app.mpos);

        RNV_HandleEvents();
        RNV_RunLogic();
        RNV_Draw();

        MPOS_MpfEnd(app.mpos, RNV_FPS);
    }

    RNV_Quit();

    return EXIT_SUCCESS;
}
