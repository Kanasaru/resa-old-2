#include "oab.h"
#include "world/flora/water.h"

extern App app;


void RNV_FieldWaterUpdate(u_int32_t gk)
{
    app.world->map[gk].layer.terrain.rect.x = app.world->map[gk].rect->x;
    app.world->map[gk].layer.terrain.rect.y = app.world->map[gk].rect->y;
}
