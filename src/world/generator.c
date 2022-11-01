#include <stdint.h>
#include <SDL2/SDL.h>

#include "mpos/mpos.h"
#include "oab.h"
#include "world.h"
#include "world/objects/island.h"
#include "world/flora/water.h"
#include "world/generator.h"

extern App app;


RNV_World * RNV_GenWorldCreate(SDL_Rect rect, int tile_s)
{
    MPOS_Grid *grd = MPOS_CreateGrid(rect.x, rect.y,
                                     rect.w, rect.h, 
                                     tile_s, tile_s);
    if (grd == NULL)
    {
        printf("RNV_Error: Error creating world grid.\n");
        return NULL;
    }
    MPOS_SetGridColor(grd, 0x56fc03);

    size_t gms = sizeof(RNV_World);
    gms += grd->t_c * sizeof(RNV_WorldField);
    RNV_World *world = (RNV_World *)malloc(gms);
    if (world == NULL)
    {
        printf("RNV_Error: Error creating world.\n");
        return NULL;
    }

    world->rect.x = rect.x;
    world->rect.y = rect.y;
    world->rect.w = rect.w * tile_s;
    world->rect.h = rect.h * tile_s;
    world->grid = grd;

    world->states.SHOW_GRID = 0;
    world->states.MOVE = RNV_WORLD_MOVE_NO;

    world->spshs.tiles = MPOS_CreateSpriteSheet(app.renderer,
                                                RNV_SPSH_TILES, 32, 32);
    if (world->spshs.tiles == NULL)
    {
        printf("Failed to create world sprite sheet: %s\n", RNV_SPSH_TILES);
        return NULL;
    }

    RNV_GenWorldInitFields(world);
    RNV_GenWorldFillWater(world);

    return world;
}

void RNV_GenWorldInitFields(RNV_World *world)
{
    for (int i = 0; i < world->grid->t_c; i++)
    {
        world->map[i].rect = &world->grid->tiles[i].rect;
        world->map[i].key = &world->grid->tiles[i].key;
        world->map[i].layer.terrain.sh = NULL;
        world->map[i].layer.structures.sh = NULL;
        world->map[i].layer.fauna.sh = NULL;
        world->map[i].layer.flora.sh = NULL;
        world->map[i].layer.objects.sh = NULL;
    }
}

void RNV_GenWorldFillWater(RNV_World *world)
{
    for (int i = 0; i < world->grid->t_c; i++)
    {
        world->map[i].layer.terrain.rect.x = world->map[i].rect->x;
        world->map[i].layer.terrain.rect.y = world->map[i].rect->y;
        world->map[i].layer.terrain.rect.w = world->map[i].rect->w;
        world->map[i].layer.terrain.rect.h = world->map[i].rect->h;
        world->map[i].layer.terrain.gk = world->grid->tiles[i].key;
        world->map[i].layer.terrain.sh = world->spshs.tiles;
        world->map[i].layer.terrain.k = RNV_SPSH_K_WATER;
        world->map[i].layer.terrain.cb = RNV_FieldWaterUpdate;
    }
}

RNV_Island * RNV_GenIslandCreate(int32_t x, int32_t y, 
                                 u_int16_t w, u_int16_t h)
{
    size_t gms = sizeof(RNV_Island);
    gms += w * h * sizeof(RNV_RawField);
    RNV_Island *island = (RNV_Island*) malloc(gms);

    if (island == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                    "[RNV Gen] Failed to create island");
        return NULL;
    }

    island->rect.x = x;
    island->rect.y = y;
    island->rect.w = w;
    island->rect.h = h;

    return island;
}

void RNV_GenIslandShape(RNV_Island *island)
{
    float e;
    float d;
    float nx;
    float ny;

    size_t i = 0;
    
    island->seed = MPOS_NoiseSeed(0, MPOS_NOISE_MAX_VAL);

    for (size_t y = 0; y < island->rect.h; y++)
    {
        for (size_t x = 0; x < island->rect.w; x++)
        {
            e = MPOS_NoisePerlin2d(x, y, 0.1f, 4.0f, &island->seed);

            nx = 2.0f * x / island->rect.w - 1.0f;
            ny = 2.0f * y / island->rect.h - 1.0f;
            d = 1.0f - (1.0f - nx * nx) * (1.0f - ny * ny);
            e = (e + (1.0f - d)) / 2.0f;

            if (e < 0.45f)
            {
                island->fields[i].layer.terrain = 0;
            } 
            else
            {
                island->fields[i].layer.terrain = 1;
            }

            i++;
        }   
    }
}

void RNV_GenPrintIslandShape(RNV_Island *island)
{
    size_t i = 0;
    printf(">------< Seed: %d >------<\n", island->seed);
    for(size_t y = 0; y < island->rect.h; y++)
    {
        printf("|");
        for(size_t x = 0; x < island->rect.w; x++)
        {
            printf("%d|", island->fields[i].layer.terrain);

            i++;
        }
        printf("\n");
    }
}
