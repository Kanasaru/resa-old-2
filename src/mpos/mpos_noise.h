/*
    MPOS_Grid:  A module of the mpos library to provide noise handling.
    License:    CC-BY-SA-4.0
    Credit:     Main source code by nowl (https://gist.github.com/nowl/828013)
*/
#ifndef __MPOS_NOISE_H__
#define __MPOS_NOISE_H__

#include <stdint.h>

#define MPOS_NOISE_MAX_HASH 255
#define MPOS_NOISE_MAX_VAL 65535


#ifdef __cplusplus
extern "C" {
#endif

u_int16_t MPOS_NoiseSeed(u_int16_t low, u_int16_t high);

u_int8_t MPOS_Noise2(u_int16_t x, u_int16_t y, u_int16_t *hash_s);

float MPOS_NoiseLinInter(float x, float y, float s);

float MPOS_NoiseSmoothInter(float x, float y, float s);

float MPOS_Noise2d(float x, float y, u_int16_t *hash_s);

float MPOS_NoisePerlin2d(float x, float y, float freq, 
                         u_int8_t depth, u_int16_t *hash_s);

#ifdef __cplusplus
}
#endif
#endif /* !__MPOS_NOISE_H__ */
