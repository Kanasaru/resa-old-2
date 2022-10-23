#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "oab.h"
#include "init.h"
#include "utl/media.h"


void RNV_InitSDL(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        printf("Error initializing SDL_image: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    app.win = SDL_CreateWindow(
        RNV_TITLE, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        RNV_SCREEN_WIDTH, 
        RNV_SCREEN_HEIGHT, 
        0
    );
    
    if (app.win == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    app.renderer = SDL_CreateRenderer(app.win, -1, SDL_RENDERER_ACCELERATED);
    
    if (!app.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
}

void RNV_InitGame(void)
{
    app.mpos = MPOS_Init();
    if (app.mpos == NULL) {
        printf("Failed to create mpos\n");
        exit(EXIT_FAILURE);
    }

    app.state.QUIT = 0;

    RNV_InitMedia();
}

void RNV_Quit(void)
{
    MPOS_Destroy(app.mpos);
    RNV_DestroyMedia();
    SDL_DestroyWindow(app.win);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
