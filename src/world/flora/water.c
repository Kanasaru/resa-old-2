#include "oab.h"
#include "utl/event.h"
#include "world/flora/water.h"

extern App app;


void RNV_FieldWaterUpdate(u_int32_t gk)
{
    RNV_Event ev;

    while (RNV_EventPollType(&ev, RNV_EV_MAP, RNV_EV_QUEUE_HOLD))
    {
        switch (ev.map.type)
        {
        case RNV_EV_MAP_MOVE:
            app.world->map[gk].layer.terrain.rect.x += ev.map.mx;
            app.world->map[gk].layer.terrain.rect.y += ev.map.my;
            break;
        }
    }
}
