#include <SDL2/SDL.h>

#include "oab.h"


void RNV_HandleEvents(void)
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            app.state.QUIT = 1;
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                app.state.QUIT = 1;
                break;
            default:
                break;
            }
            break;
        }
    }
}
