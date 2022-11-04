/*
    MPOS_Sprite: A module of the mpos library using the SDL library and 
                 SDL_image libary to provide sprite and sprite sheet handling.
    License:     CC-BY-SA-4.0
*/
#ifndef __MPOS_SPRITE_H__
#define __MPOS_SPRITE_H__

#include <SDL2/SDL.h>


/* MPOS_SpriteSheet: represents a sprite sheet */

typedef struct
{
    SDL_Texture *t;         /* sprite sheet texture */
    SDL_Color *ck;          /* color key */
    uint32_t cc;            /* clip count */
    SDL_Rect clips[];       /* clip locations */
} MPOS_SpriteSheet;


/* MPOS_Sprite: represents a sprite */

typedef struct
{
    uint32_t i;             /* sprite index in sprite group */
    uint32_t gk;            /* grid key */
    MPOS_SpriteSheet *sh;   /* sprite sheet pointer */
    uint32_t k;             /* key in sprite sheet */
    SDL_Rect rect;          /* position (x, y) and size (w, h) */
    SDL_Rect iso_rect;
    void (*cb)(uint32_t );  /* pointer to update function */
} MPOS_Sprite;


/* MPOS_SpriteGroup: represents a sprite group */

typedef struct
{
    uint32_t sc;            /* amount of sprites */
    MPOS_Sprite sprites[];  /* sprites */
} MPOS_SpriteGroup;


/* creates a sprite sheet from file */
MPOS_SpriteSheet * MPOS_CreateSpriteSheet(SDL_Renderer *r, const char *p,
                                          uint32_t t_w, uint32_t t_h);

/* draws clip from given sprite sheet and k to given renderer and rect */
void MPOS_DrawClip(MPOS_SpriteSheet *sh, uint32_t k, SDL_Renderer *r, SDL_Rect d);

/* draws given sprite to given renderer */
void MPOS_SpriteDraw(MPOS_Sprite sprite, SDL_Renderer *r);

void MPOS_SpriteDrawIso(MPOS_Sprite sprite, SDL_Renderer *r);

/* creates a sprite group */
MPOS_SpriteGroup * MPOS_CreateSpriteGroup(void);

/* adds given sprite to given sprite group */
void MPOS_SpriteGroupAdd(MPOS_SpriteGroup **grp, MPOS_Sprite *sprite);

/* removes given sprite from given sprite group */
void MPOS_SpriteGroupRemove(MPOS_SpriteGroup **grp, MPOS_Sprite *sprite);

/* draws all sprites of given group to given renderer */
void MPOS_SpriteGroupDraw(MPOS_SpriteGroup *grp, SDL_Renderer *r);

/* calls the update/callback function of each sprite in given group */
void MPOS_SpriteGroupUpdate(MPOS_SpriteGroup *grp);

/* calls the update/callback function from given sprite */
void MPOS_SpriteUpdate(MPOS_Sprite *sprite);

#endif /* !__MPOS_SPRITE_H__ */
