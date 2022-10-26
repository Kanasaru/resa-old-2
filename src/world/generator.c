#include <stdint.h>
#include <SDL2/SDL.h>

#include "mpos/mpos.h"
#include "world/generator.h"
#include "world/objects/island.h"


void RNV_GenWorldCreate(void)
{
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
    
    island->seeds.shape = MPOS_NoiseSeed(0, MPOS_NOISE_MAX_VAL);

    for (size_t y = 0; y < island->rect.h; y++)
    {
        for (size_t x = 0; x < island->rect.w; x++)
        {
            e = MPOS_NoisePerlin2d(x, y, 0.1f, 4.0f, &island->seeds.shape);

            nx = 2.0f * x / island->rect.w - 1.0f;
            ny = 2.0f * y / island->rect.h - 1.0f;
            d = 1.0f - (1.0f - nx * nx) * (1.0f - ny * ny);
            e = (e + (1.0f - d)) / 2.0f;

            if (e < 0.45f)
            {
                island->fields[i].layer.water = 0;
                island->fields[i].layer.island = -1;
            } 
            else
            {
                island->fields[i].layer.island = 1;
                island->fields[i].layer.water = -1;
            }

            i++;
        }   
    }
}

void RNV_GenPrintIslandShape(RNV_Island *island)
{
    size_t i = 0;
    printf(">------< Seed: %d >------<\n", island->seeds.shape);
    for(size_t y = 0; y < island->rect.h; y++)
    {
        printf("|");
        for(size_t x = 0; x < island->rect.w; x++)
        {
            if (island->fields[i].layer.water != -1)
                printf("0|");
            if (island->fields[i].layer.island != -1)
                printf("1|");

            i++;
        }
        printf("\n");
    }
}
