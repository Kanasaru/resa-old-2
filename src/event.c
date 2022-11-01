#include <SDL2/SDL.h>

#include "mpos/mpos.h"
#include "oab.h"
#include "utl/media.h"


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
            case SDLK_F3:
                if (MPOS_TakeScreenshot(app.renderer, "bin/") == 0){
                    RNV_PlaySound(media.sounds.screenshot);
                }
                break;
            case SDLK_1:
                RNV_PauseMusic();
                break;
            case SDLK_2:
                Mix_HaltMusic();
                break;
            case SDLK_3:
                RNV_MusicVolume(-8);
                break;
            case SDLK_4:
                RNV_MusicVolume(8);
                break;
            case SDLK_5:
                RNV_SoundVolume(-8);
                break;
            case SDLK_6:
                RNV_SoundVolume(8);
                break;
            default:
                break;
            }
            break;
        }

        RNV_WorldHandleEvent(app.world, event);
    }
}
