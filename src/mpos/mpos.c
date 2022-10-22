/*
    MPOS:       A library using the SDL library and SDL_image libary.
    License:    CC-BY-SA-4.0
*/
#include <SDL2/SDL.h>

#include "mpos.h"


MPOS * MPOS_Init(void)
{
    size_t gms = sizeof(MPOS);
    MPOS *mpos = (MPOS*) malloc(gms);

    if (mpos == NULL)
    {
        printf("[MPOS] Error initialising MPOS\n");
        return NULL;
    }

    mpos->time.fps = 0;
    mpos->time.fps_c = 0;
    mpos->time.prev_time = SDL_GetTicks();
    mpos->time.fps_n = mpos->time.prev_time + 1000;
    mpos->time.dt = 0;
    mpos->time.mpf_s = 0;
    mpos->time.mpf_e = 0;

    return mpos;
}

void MPOS_Destroy(MPOS * mpos)
{
    free(mpos);
}

void MPOS_MpfStart(MPOS * mpos)
{
    mpos->time.mpf_s = SDL_GetPerformanceCounter();
}

void MPOS_MpfEnd(MPOS * mpos, u_int32_t fps)
{
    mpos->time.mpf_e = SDL_GetPerformanceCounter();

    if (fps > 0)
    {
        float elapsedMS = (mpos->time.mpf_e - mpos->time.mpf_s) / 
                          (float) SDL_GetPerformanceFrequency() * 1000.0f;
        int32_t wait = floor((1000.0f / fps) - elapsedMS);
        if (wait > 0)
        {
            SDL_Delay(wait);
        }
    }
}

void MPOS_DtFps(MPOS * mpos)
{
    u_int32_t now = SDL_GetTicks();
    mpos->time.dt = (now - mpos->time.prev_time) / 1000.0f;
    mpos->time.prev_time = now;
    
    mpos->time.fps_c++;
    if (now >= mpos->time.fps_n)
    {
        mpos->time.fps = mpos->time.fps_c;
        mpos->time.fps_c = 0;

        mpos->time.fps_n = now + 1000;
    }
}
