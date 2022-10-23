/*
    MPOS:       A library using the SDL library and SDL_image libary.
    License:    CC-BY-SA-4.0
*/
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mpos.h"


MPOS * MPOS_Init(void)
{
    size_t gms = sizeof(MPOS);
    MPOS *mpos = (MPOS*) malloc(gms);

    if (mpos == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[MPOS] Error initialising MPOS");
        return NULL;
    }

    mpos->time.fps = 0;
    mpos->time.fps_c = 0;
    mpos->time.prev_time = SDL_GetTicks();
    mpos->time.fps_n = mpos->time.prev_time + 1000;
    mpos->time.dt = 0;
    mpos->time.mpf_s = 0;
    mpos->time.mpf_e = 0;
    mpos->time.tc_c = 0;

    return mpos;
}

void MPOS_Destroy(MPOS *mpos)
{
    free(mpos);
}

void MPOS_MpfStart(MPOS *mpos)
{
    mpos->time.mpf_s = SDL_GetPerformanceCounter();
}

void MPOS_MpfEnd(MPOS *mpos, u_int32_t fps)
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

void MPOS_DtFps(MPOS *mpos)
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

void MPOS_TimerStart(MPOS *mpos, uint32_t r, const char *n)
{
    mpos->time.tc_s = SDL_GetPerformanceCounter();
    mpos->time.tc_r = r;
    mpos->time.tc_n = n;
}

void MPOS_TimerEnd(MPOS *mpos)
{
    if (mpos->time.tc_c < mpos->time.tc_r)
    {
        mpos->time.tc_e = SDL_GetPerformanceCounter();
        float elapsedMS = (mpos->time.tc_e - mpos->time.tc_s) / 
                          (float) SDL_GetPerformanceFrequency() * 1000.0f;
        
        size_t lgth = snprintf(NULL, 0, MPOS_TIMER_FORMAT, 
                               mpos->time.tc_n, elapsedMS) + 1;
        char *str = malloc(lgth);
        snprintf(str, lgth, MPOS_TIMER_FORMAT, mpos->time.tc_n, elapsedMS);

        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", str);

        mpos->time.tc_c++;
        free(str);
    }
}

void MPOS_TimerReset(MPOS *mpos)
{
    mpos->time.tc_c = 0;
}

u_int32_t MPOS_TakeScreenshot(SDL_Renderer *r, const char *fp)
{
    SDL_Rect size;
    SDL_Surface *sf = NULL;

    time_t rawtime = time(NULL);
    if (rawtime == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[MPOS] time() function failed for screenshot");
        return 1;
    }
    struct tm *ptm = localtime(&rawtime);

    size_t lgth = snprintf(NULL, 0, MPOS_SCREENSHOT_FORMAT, fp, "Screenshot", 
                           ptm->tm_mday, ptm->tm_mon, ptm->tm_year + 1900,
                           ptm->tm_hour, ptm->tm_min, ptm->tm_sec,
                           ".png") + 1;
    char *str = malloc(lgth);
    snprintf(str, lgth, MPOS_SCREENSHOT_FORMAT, fp, "Screenshot", 
             ptm->tm_mday, ptm->tm_mon, ptm->tm_year + 1900,
             ptm->tm_hour, ptm->tm_min, ptm->tm_sec,
             ".png");

    SDL_RenderGetViewport(r, &size);
    
    sf = SDL_CreateRGBSurface(0, size.w, size.h, 32, 0, 0, 0, 0);
    if (sf == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[MPOS] Cannot create surface for screenshot");
        free(str);
        return 1;
    }
    if (SDL_RenderReadPixels(r, NULL, 
                             sf->format->format, 
                             sf->pixels, 
                             sf->pitch) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[MPOS] Cannot read from surface for screenshot");
        SDL_FreeSurface(sf);
        free(str);
        return 1;
    }
    if (IMG_SavePNG(sf, str) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[MPOS] Could not save screenshot to '%s'", str);
        SDL_FreeSurface(sf);
        free(str);
        return 1;
    }

    SDL_FreeSurface(sf);
    free(str);
    return 0;
}
