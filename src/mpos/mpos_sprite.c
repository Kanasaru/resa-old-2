/*
    MPOS_Sprite: A module of the mpos library using the SDL library and 
                 SDL_image libary to provide sprite and sprite sheet handling.
    License:     CC-BY-SA-4.0
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mpos_sprite.h"


MPOS_SpriteSheet * MPOS_CreateSpriteSheet(SDL_Renderer *r, const char *p,
                                          uint32_t t_w, uint32_t t_h)
{
    SDL_Surface *img_s = IMG_Load(p);
    if (img_s == NULL)
    {
        printf("MPOS_Sprite: Error loading image %s (%s)\n", 
                p, IMG_GetError());
        return NULL;
    }

    size_t gms = sizeof(MPOS_SpriteSheet);
    gms += img_s->w / t_w * img_s->h / t_h * sizeof(SDL_Rect);
    MPOS_SpriteSheet *spsh = (MPOS_SpriteSheet*) malloc(gms);

    spsh->cc = img_s->w / t_w * img_s->h / t_h - 1;
    spsh->t = SDL_CreateTextureFromSurface(r, img_s);
    if (spsh->t == NULL)
    {
        printf("MPOS_Sprite: Error creating texture from %s! (%s)\n",
                p, SDL_GetError());
    }
    else
    {
        uint32_t k = 0;
        uint32_t x = 0;
        uint32_t y = 0;
        for (size_t i = 0; i < img_s->h / t_h; i++)
        {
            for (size_t j = 0; j < img_s->w / t_w; j++)
            {
                spsh->clips[k].x = x;
                spsh->clips[k].y = y; 
                spsh->clips[k].w = t_w;
                spsh->clips[k].h = t_h;
                x = (j + 1) * t_w;
                k++;
            }
            x = 0;
            y = (i + 1) * t_h;
        }
    }
    SDL_FreeSurface(img_s);
    return spsh;
}

void MPOS_DrawClip(MPOS_SpriteSheet *sh, uint32_t k, SDL_Renderer *r, SDL_Rect d)
{
    if (k <= sh->cc)
        SDL_RenderCopy(r, sh->t, &sh->clips[k], &d);
}

void MPOS_SpriteDraw(MPOS_Sprite sprite, SDL_Renderer *r)
{
    MPOS_DrawClip(sprite.sh, sprite.k, r, sprite.rect);
}

MPOS_SpriteGroup * MPOS_CreateSpriteGroup(void)
{
    size_t gms = sizeof(MPOS_SpriteGroup);
    MPOS_SpriteGroup *grp = (MPOS_SpriteGroup*) malloc(gms);

    if (grp != NULL)
    {
        grp->sc = 0;
    }

    return grp;
}

void MPOS_SpriteGroupAdd(MPOS_SpriteGroup **grp, MPOS_Sprite *sprite)
{
    size_t gms = sizeof(MPOS_SpriteGroup);
    gms += ((*grp)->sc + 1) * sizeof(MPOS_Sprite);
    *grp = (MPOS_SpriteGroup*) realloc(*grp, gms);

    if (grp != NULL)
    {
        (*grp)->sprites[(*grp)->sc].i = (*grp)->sc;
        (*grp)->sprites[(*grp)->sc].sh = sprite->sh;
        (*grp)->sprites[(*grp)->sc].k = sprite->k;
        (*grp)->sprites[(*grp)->sc].rect = sprite->rect;
        (*grp)->sprites[(*grp)->sc].cb = sprite->cb;

        (*grp)->sc++;
    }
}

void MPOS_SpriteGroupRemove(MPOS_SpriteGroup **grp, MPOS_Sprite *sprite)
{
    int32_t ak = -1;

    for (size_t i = 0; i < (*grp)->sc; i++)
    {
        if ((*grp)->sprites[i].i == i)
        {
            ak = i;
            break;
        }
    }

    if (ak == -1)
    {
        return;
    }

    for (size_t j = ak; j < (*grp)->sc - 1; j++)
    {
        (*grp)->sprites[j].i = j;
        (*grp)->sprites[j].sh = (*grp)->sprites[j + 1].sh;
        (*grp)->sprites[j].k = (*grp)->sprites[j + 1].k;
        (*grp)->sprites[j].rect = (*grp)->sprites[j + 1].rect;
        (*grp)->sprites[j].cb = (*grp)->sprites[j + 1].cb;
    }
    (*grp)->sc--;

    size_t gms = sizeof(MPOS_SpriteGroup);
    gms += (*grp)->sc * sizeof(MPOS_Sprite);
    *grp = (MPOS_SpriteGroup*) realloc(*grp, gms);
}

void MPOS_SpriteGroupDraw(MPOS_SpriteGroup *grp, SDL_Renderer *r)
{
    if (grp != NULL)
    {
        for (size_t i = 0; i < grp->sc; i++)
        {
            MPOS_DrawClip(grp->sprites[i].sh,
                          grp->sprites[i].k,
                          r,
                          grp->sprites[i].rect);
        }
    }
}

void MPOS_SpriteGroupUpdate(MPOS_SpriteGroup *grp)
{
    if (grp != NULL)
    {
        for (size_t i = 0; i < grp->sc; i++)
        {
            MPOS_SpriteUpdate(&grp->sprites[i]);
        }
    }
}

void MPOS_SpriteUpdate(MPOS_Sprite *sprite)
{
    if (sprite->cb != NULL)
    {
        sprite->cb(sprite->gk);
    }
}
