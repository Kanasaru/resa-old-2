/*
    MPOS:       A library using the SDL library and SDL_image libary.
    License:    CC-BY-SA-4.0
*/
#ifndef __MPOS_H__
#define __MPOS_H__

#include <stdint.h>
#include <SDL2/SDL.h>

#include "mpos/mpos_noise.h"

#define MPOS_TIMER_FORMAT "%s: %f ms"
#define MPOS_SCREENSHOT_FORMAT "%s%s_%02d-%02d-%02d_%02d-%02d-%02d%s"

typedef struct
{
    struct
    {
        u_int32_t fps;          /* current frame rate */
        u_int32_t fps_c;        /* frame rate counter */
        u_int32_t fps_n;        /* frame rate timer */
        u_int32_t prev_time;    /* delta time timer */
        u_int32_t dt;           /* current delta time */
        u_int64_t mpf_s;        /* ms per frame at start */
        u_int64_t mpf_e;        /* ms per frame at end */
        u_int64_t tc_s;         /* ms in time capping at start */
        u_int64_t tc_e;         /* ms in time capping at end */
        u_int32_t tc_c;         /* time capping counter */
        u_int32_t tc_r;         /* rounds of time capping */
        const char *tc_n;       /* time capping name */
    } time;
} MPOS;


#ifdef __cplusplus
extern "C" {
#endif

/* initialises MPOS */
MPOS * MPOS_Init(void);

/* destroys MPOS */
void MPOS_Destroy(MPOS * mpos);

/* calculates fps and delta time */
void MPOS_DtFps(MPOS * mpos);

/* starts timer for fps capping */
void MPOS_MpfStart(MPOS * mpos);

/* caps fps by given frame rate */
void MPOS_MpfEnd(MPOS * mpos, u_int32_t fps);

/* starts development timer */
void MPOS_TimerStart(MPOS *mpos, uint32_t r, const char *n);

/* ends development timer */
void MPOS_TimerEnd(MPOS *mpos);

/* resets development timer */
void MPOS_TimerReset(MPOS *mpos);

/* takes a screenshot from given renderer to given filename */
u_int32_t MPOS_TakeScreenshot(SDL_Renderer *r, const char *f);

#ifdef __cplusplus
}
#endif
#endif /* !__MPOS_H__ */
