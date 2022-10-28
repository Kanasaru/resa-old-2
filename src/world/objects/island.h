#ifndef __RNV_ISLAND_H__
#define __RNV_ISLAND_H__

#include <stdint.h>
#include <SDL2/SDL.h>

#include "mpos/mpos.h"
#include "world/objects/fields.h"


typedef struct
{
    SDL_Rect rect;
    u_int16_t seed;
    RNV_RawField fields[];
} RNV_Island;

#endif /* !__RNV_ISLAND_H__ */
