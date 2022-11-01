#ifndef __RNV_FIELDS_H__
#define __RNV_FIELDS_H__

#include <SDL2/SDL.h>

#include "mpos/mpos.h"


typedef struct
{
    struct
    {
        int32_t terrain;
        int32_t structures;
        int32_t fauna;
        int32_t flora;
        int32_t objects;
    } layer;
} RNV_RawField;

typedef struct
{
    SDL_Rect *rect;
    u_int32_t *key;
    struct
    {
        MPOS_Sprite terrain;
        MPOS_Sprite structures;
        MPOS_Sprite fauna;
        MPOS_Sprite flora;
        MPOS_Sprite objects;
    } layer;
} RNV_WorldField;

#endif /* !__RNV_FIELDS_H__ */
