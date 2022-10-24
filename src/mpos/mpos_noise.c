/*
    MPOS_Grid:  A module of the mpos library to provide noise handling.
    License:    CC-BY-SA-4.0
    Credit:     Source code base by nowl (https://gist.github.com/nowl/828013)
*/
#include <stdint.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "mpos_noise.h"


static int hash[] = {
    247, 26, 111, 236, 149, 188, 121, 44, 155, 147, 99, 1, 215, 180, 10, 30, 
    20, 82, 130, 81, 67, 250, 68, 25, 207, 122, 38, 171, 201, 154, 65, 243, 
    120, 169, 134, 110, 233, 178, 145, 190, 75, 118, 104, 86, 248, 196, 21, 95, 
    8, 168, 164, 227, 107, 223, 33, 101, 240, 173, 197, 179, 176, 208, 202, 
    245, 214, 232, 7, 203, 132, 172, 113, 52, 141, 211, 200, 28, 84, 249, 15, 
    79, 209, 27, 78, 193, 69, 213, 238, 159, 63, 157, 220, 194, 60, 6, 93, 204, 
    119, 48, 16, 139, 131, 62, 206, 138, 251, 184, 174, 66, 34, 115, 135, 150, 
    3, 18, 117, 9, 205, 55, 98, 136, 224, 152, 108, 222, 29, 102, 151, 22, 175, 
    50, 199, 242, 19, 185, 91, 187, 85, 59, 218, 96, 239, 142, 124, 0, 42, 255, 
    2, 158, 231, 140, 4, 230, 156, 39, 31, 73, 228, 35, 161, 46, 210, 53, 166, 
    125, 24, 106, 12, 217, 89, 148, 167, 241, 191, 5, 64, 212, 163, 123, 61, 
    105, 76, 90, 177, 254, 129, 186, 87, 170, 237, 114, 40, 14, 146, 143, 37, 
    97, 80, 126, 195, 83, 58, 219, 13, 189, 246, 235, 57, 32, 225, 112, 182, 
    244, 47, 234, 198, 49, 43, 74, 36, 253, 229, 109, 192, 162, 45, 56, 153, 
    77, 103, 221, 181, 144, 137, 116, 17, 183, 71, 128, 94, 133, 23, 226, 92, 
    160, 216, 11, 100, 252, 70, 165, 54, 51, 127, 41, 88, 72
};

u_int16_t MPOS_NoiseSeed(u_int16_t low, u_int16_t high)
{
    srand(time(0));
    return (rand() % (high - low + 1)) + low;
}

u_int8_t MPOS_Noise2(u_int16_t x, u_int16_t y, u_int16_t *hash_s)
{
    u_int16_t tmp;

    if ((y + (*hash_s)) > MPOS_NOISE_MAX_VAL)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "[MPOS Noise] MPOS_NOISE_MAX_VAL reached. Used %d.",
                    MPOS_NOISE_MAX_VAL);
        tmp = MPOS_NOISE_MAX_VAL;
    }
    else
    {
        tmp = y + (*hash_s);
    }
    tmp = hash[tmp % (MPOS_NOISE_MAX_HASH + 1)];
    if ((tmp + x) > MPOS_NOISE_MAX_VAL)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "[MPOS Noise] MPOS_NOISE_MAX_VAL reached. Used %d.",
                    MPOS_NOISE_MAX_VAL);
        tmp = MPOS_NOISE_MAX_VAL;
    }
    else
    {
        tmp += x;
    }

    return hash[tmp % (MPOS_NOISE_MAX_HASH + 1)];
}

float MPOS_NoiseLinInter(float x, float y, float s)
{
    return x + s * (y - x);
}

float MPOS_NoiseSmoothInter(float x, float y, float s)
{
    return MPOS_NoiseLinInter(x, y, s * s * (3 - 2 * s));
}

float MPOS_Noise2d(float x, float y, u_int16_t *hash_s)
{
    u_int32_t x_int = x;
    u_int32_t y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    u_int8_t s = MPOS_Noise2(x_int, y_int, hash_s);
    u_int8_t t = MPOS_Noise2(x_int + 1, y_int, hash_s);
    u_int8_t u = MPOS_Noise2(x_int, y_int + 1, hash_s);
    u_int8_t v = MPOS_Noise2(x_int + 1, y_int + 1, hash_s);
    float low = MPOS_NoiseSmoothInter(s, t, x_frac);
    float high = MPOS_NoiseSmoothInter(u, v, x_frac);

    return MPOS_NoiseSmoothInter(low, high, y_frac);
}

float MPOS_NoisePerlin2d(float x, float y, float freq, 
                         u_int8_t depth, u_int16_t *hash_s)
{
    float xa = x * freq;
    float ya = y * freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    for (size_t i = 0; i < depth; i++)
    {
        div += MPOS_NOISE_MAX_HASH * amp;
        fin += MPOS_Noise2d(xa, ya, hash_s) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}
