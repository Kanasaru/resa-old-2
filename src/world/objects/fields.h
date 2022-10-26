#ifndef __RNV_FIELDS_H__
#define __RNV_FIELDS_H__

#include <SDL2/SDL.h>

#include "mpos/mpos.h"

typedef struct
{
    struct
    {
        int32_t water;
        int32_t island;
    } layer;
} RNV_RawField;

typedef struct
{
    SDL_Rect *rect;
    int *key;
    struct
    {
        MPOS_Sprite water;
        MPOS_Sprite island;
    } layer;
} RNV_WorldField;

#endif /* !__RNV_FIELDS_H__ */
