/*
    MPOS:       A library using the SDL library and SDL_image libary.
    License:    CC-BY-SA-4.0
*/
#ifndef __MPOS_H__
#define __MPOS_H__

#include <stdint.h>


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
    } time;
} MPOS;


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

#endif /* !__MPOS_H__ */
