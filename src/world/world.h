#ifndef __RNV_WORLD_H__
#define __RNV_WORLD_H__

#include <SDL2/SDL.h>

#include "mpos/mpos.h"
#include "objects/fields.h"
#include "objects/island.h"

#define RNV_WORLD_WIDTH  100
#define RNV_WORLD_HEIGHT 60
#define RNV_WORLD_TILE_WIDTH 32
#define RNV_WORLD_TILE_HEIGHT 32

#define RNV_SPSH_TILES "res/sprites/rnv_tiles_32x32.png"
#define RNV_SPSH_K_WATER 2
#define RNV_SPSH_K_GRAS 3

#define RNV_WORLD_MOVE_NO    0x00
#define RNV_WORLD_MOVE_UP    0x01
#define RNV_WORLD_MOVE_DOWN  0x02
#define RNV_WORLD_MOVE_LEFT  0x04
#define RNV_WORLD_MOVE_RIGHT 0x08
#define RNV_WORLD_MOVE_TL    0x05
#define RNV_WORLD_MOVE_TR    0x09
#define RNV_WORLD_MOVE_BL    0x06
#define RNV_WORLD_MOVE_BR    0x0A
#define RNV_WORLD_MOVE_SPEED 10

#define RNV_WORLD_ISLAND_COUNT 11


typedef struct
{
    SDL_Rect rect;
    SDL_Rect dstrect;
    SDL_Texture *texture;
    MPOS_Grid *grid;
    struct
    {
        MPOS_SpriteSheet *tiles;
    } spshs;
    struct
    {
        uint8_t SHOW_GRID;
        uint8_t MOVE;
    } states;
    u_int16_t seed[RNV_WORLD_ISLAND_COUNT];
    RNV_WorldField map[];
} RNV_World;


void RNV_WorldHandleEvent(RNV_World *world, SDL_Event event);

void RNV_WorldMove(RNV_World *world);

void RNV_WorldUpdate(RNV_World *world);

void RNV_WorldDraw(RNV_World *world, SDL_Renderer *r);

void RNV_WorldSetRenderRect(RNV_World *world, SDL_Rect rect);

#endif /* !__RNV_WORLD_H__ */
