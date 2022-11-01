#ifndef __RNV_GENERATOR_H__
#define __RNV_GENERATOR_H__

#include <stdint.h>
#include <SDL2/SDL.h>

#include "objects/island.h"


#define RNV_GEN_ISLANDSIZE_B_W 50
#define RNV_GEN_ISLANDSIZE_B_H 50
#define RNV_GEN_ISLANDSIZE_M_W 40
#define RNV_GEN_ISLANDSIZE_M_H 40
#define RNV_GEN_ISLANDSIZE_S_W 30
#define RNV_GEN_ISLANDSIZE_S_H 30

#ifdef __cplusplus
extern "C" {
#endif

RNV_World * RNV_GenWorldCreate(SDL_Rect rect, int tile_s);

void RNV_GenWorldInitFields(RNV_World *world);

void RNV_GenWorldFillWater(RNV_World *world);

RNV_Island * RNV_GenIslandCreate(int32_t x, int32_t y, 
                                 u_int16_t w, u_int16_t h);

void RNV_GenIslandShape(RNV_Island *island);

void RNV_GenPrintIslandShape(RNV_Island *island);

void RNV_GenIslandFlora(void);

#ifdef __cplusplus
}
#endif
#endif /* !__RNV_GENERATOR_H__ */
