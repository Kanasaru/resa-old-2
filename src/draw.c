#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "oab.h"
#include "draw.h"


void RNV_Draw(void)
{
    RNV_PrepareScreen();

    RNV_WorldDraw(app.world, app.renderer);

    RNV_DrawPanel();

    RNV_PresentScreen();
}

void RNV_PrepareScreen(void)
{
    SDL_SetRenderDrawColor(app.renderer, 0x24, 0x24, 0x24, 0xff);
    SDL_RenderClear(app.renderer);
}

void RNV_PresentScreen(void)
{
    SDL_RenderPresent(app.renderer);
}

void RNV_DrawPanel(void)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Texture *text_texture;

    SDL_Color c_txt = { 0xff, 0xff, 0xff };
    SDL_Color c_bg = { 0x80, 0x00, 0x00 };
    SDL_Rect rect = { 0, 0, RNV_SCREEN_WIDTH, RNV_PANEL_HEIGHT };

    size_t lgth_title = snprintf(NULL, 0, "%s | ", RNV_TITLE);
    size_t lgth_version = snprintf(NULL, 0, "v%s | ", RNV_VERSION);
    size_t lgth_fps = snprintf(NULL, 0, "FPS: %d", app.mpos->time.fps);
    size_t lgth_str = lgth_title + lgth_version + lgth_fps + 1;
    size_t pad  = (size_t) ((RNV_PANEL_HEIGHT - 
                             RNV_STD_FONT_SIZE * 0.75) / 2 - 1);

    char *str = malloc(lgth_str);
    snprintf(str, lgth_str, "%s | v%s | FPS: %d", 
             RNV_TITLE, RNV_VERSION, app.mpos->time.fps);
    
    SDL_SetRenderDrawColor(app.renderer, c_bg.r, c_bg.g, c_bg.b, 0xff);
    SDL_RenderFillRect(app.renderer, &rect);

    font = TTF_OpenFont(RNV_STD_FONT, RNV_STD_FONT_SIZE * 0.75);
    if (!font) {
        printf("%s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    text = TTF_RenderUTF8_Blended(font, str, c_txt);
    if (!text) {
        printf("%s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    text_texture = SDL_CreateTextureFromSurface(app.renderer, text);
    SDL_Rect dest = { pad, pad, text->w, text->h };
    
    SDL_RenderCopy(app.renderer, text_texture, 0, &dest);
    
    TTF_CloseFont(font);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
    free(str);
}
