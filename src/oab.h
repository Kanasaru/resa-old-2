#ifndef __RNV_OAB_H__
#define __RNV_OAB_H__

#include <SDL2/SDL.h>

#include "mpos/mpos.h"


#define RNV_SCREEN_WIDTH  800
#define RNV_SCREEN_HEIGHT 600
#define RNV_FPS           60
#define RNV_PANEL_HEIGHT  30
#define RNV_STD_FONT_SIZE 18
#define RNV_STD_FONT      "res/fonts/NotoSans-Regular.ttf"

#define RNV_TITLE         "Resa - Nya Världar"
#define RNV_VERSION       "0.0.0-alpha"


typedef struct
{
    SDL_Window *win;
    SDL_Renderer *renderer;
    MPOS *mpos;
    struct
    {
        u_int16_t QUIT;           /* game quitting */
    } state;
} App;

App app;

#endif /* !__RNV_OAB_H__ */
