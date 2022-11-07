#include <SDL2/SDL.h>

#include "mpos/mpos.h"
#include "oab.h"
#include "utl/media.h"
#include "event.h"


extern App app;


void RNV_HandleEvents(void)
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            app.state.QUIT = 1;
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                app.state.QUIT = 1;
                break;
            case SDLK_F3:
                if (MPOS_TakeScreenshot(app.renderer, "bin/") == 0){
                    RNV_PlaySound(media.sounds.screenshot);
                }
                break;
            case SDLK_1:
                RNV_PauseMusic();
                break;
            case SDLK_2:
                Mix_HaltMusic();
                break;
            case SDLK_3:
                RNV_MusicVolume(-8);
                break;
            case SDLK_4:
                RNV_MusicVolume(8);
                break;
            case SDLK_5:
                RNV_SoundVolume(-8);
                break;
            case SDLK_6:
                RNV_SoundVolume(8);
                break;
            default:
                break;
            }
            break;
        }

        RNV_WorldHandleEvent(app.world, event);
    }
}

RNV_EventQueue * RNV_EventQueueCreate(void)
{
    size_t gms = sizeof(RNV_EventQueue);
    RNV_EventQueue *eq = (RNV_EventQueue*) malloc(gms);

    if (eq != NULL)
    {
        eq->ev_c = 0;
        eq->ev_qc = 0;
    }

    return eq;
}

u_int32_t RNV_EventPoll(RNV_Event *event, u_int8_t flag)
{
    if (app.eq->ev_c == 0)
    {
        return 0;
    }

    if (app.eq->ev_qc >= app.eq->ev_c)
    {
        app.eq->ev_qc = 0;
        return 0;
    }

    (*event) = app.eq->events[app.eq->ev_qc];

    if (flag == RNV_EV_QUEUE_DELETE)
    {
        RNV_EventRemoveFromQueue(app.eq->ev_qc);
    }

    app.eq->ev_qc++;

    return 1;
}

u_int32_t RNV_EventPollType(RNV_Event *event, uint16_t type, u_int8_t flag)
{
    if (app.eq->ev_c == 0)
    {
        return 0;
    }

    if (app.eq->ev_qc >= app.eq->ev_c)
    {
        app.eq->ev_qc = 0;
        return 0;
    }

    while (app.eq->ev_qc < app.eq->ev_c)
    {
        if (app.eq->events[app.eq->ev_qc].type == type)
        {
            (*event) = app.eq->events[app.eq->ev_qc];
            if (flag == RNV_EV_QUEUE_DELETE)
            {
                RNV_EventRemoveFromQueue(app.eq->ev_qc);
            }
            app.eq->ev_qc++;
            return 1;
        }
        app.eq->ev_qc++;
    }

    return 0;
}

void RNV_EventPush(RNV_Event event)
{
    size_t gms = sizeof(RNV_EventQueue);
    gms += (app.eq->ev_c + 1) * sizeof(RNV_Event);
    app.eq = (RNV_EventQueue*) realloc(app.eq, gms);

    if (app.eq != NULL)
    {
        app.eq->events[app.eq->ev_c] = event;

        app.eq->ev_c++;
    }
}

void RNV_EventRemoveFromQueue(u_int32_t e_k)
{
    for (size_t j = e_k; j < app.eq->ev_c - 1; j++)
    {
        app.eq->events[j] = app.eq->events[j + 1];
    }
    app.eq->ev_c--;

    size_t gms = sizeof(RNV_EventQueue);
    gms += app.eq->ev_c * sizeof(RNV_Event);
    app.eq = (RNV_EventQueue*) realloc(app.eq, gms);
}

void RNV_EventRemoveTypeFromQueue(uint16_t type)
{
    for (size_t i = 0; i < app.eq->ev_c; i++)
    {
        if (app.eq->events[i].type == type)
        {
            RNV_EventRemoveFromQueue(i);
        }
    }
}

void RNV_EventQueueDelete(void)
{
    free(app.eq);
}

void RNV_EventQueueReset(void)
{
    if (app.eq != NULL)
    {
        RNV_EventQueueDelete();
    }

    size_t gms = sizeof(RNV_EventQueue);
    app.eq = (RNV_EventQueue*) malloc(gms);

    if (app.eq != NULL)
    {
        app.eq->ev_c = 0;
        app.eq->ev_qc = 0;
    }
}
