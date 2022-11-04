/*
    MPOS_Grid: A module of the mpos library usind the SDL library to provide 
               basic grid and isometric grid handling.
    License:   CC-BY-SA-4.0
*/
#ifndef __MPOS_GRID_H__
#define __MPOS_GRID_H__

#include <SDL2/SDL.h>


/* MPOS_Vector2: represents a point */

typedef struct
{
    int32_t x;
    int32_t y;
} MPOS_Vector2;


/* MPOS_Matrix: represents a matrix */

typedef struct
{
    int32_t a;
    int32_t b;
    int32_t c;
    int32_t d;
} MPOS_Matrix;


/* MPOS_GridTile: structure for single tile information  */

typedef struct
{
    u_int32_t key;                /* key in grid tile array */
    u_int32_t row;                /* row number in grid */
    u_int32_t col;                /* col number in grid */
    SDL_Rect rect;                /* position (x, y) and size (w, h) */
} MPOS_GridTile;


/* MPOS_GridTileNeighbors: structure for tile neighbors */

typedef struct
{
    u_int32_t l;                  /* key of left neighbor */
    u_int32_t r;                  /* key of right neighbor */
    u_int32_t t;                  /* key of top neighbor */
    u_int32_t b;                  /* key of bottom neighbor */
    u_int32_t tl;                 /* key of top left neighbor */
    u_int32_t tr;                 /* key of top right neighbor */
    u_int32_t bl;                 /* key of bottom left neighbor */
    u_int32_t br;                 /* key of bottom right neighbor */
} MPOS_GridTileNeighbors;


/* MPOS_Grid: structure for all grid information */

typedef struct
{
    SDL_Rect rect;                /* position (x, y), cols (w) and rows (h) */
    u_int32_t t_w;                /* single tile with */
    u_int32_t t_h;                /* single tile height */
    SDL_Color c;                  /* grid drawing color */
    u_int32_t t_c;                /* tile count in tile array */
    MPOS_GridTile tiles[];        /* array of all tiles in grid */
} MPOS_Grid;


/* creates a tile */
MPOS_GridTile MPOS_CreateGridTile(u_int32_t k, int32_t x, int32_t y, 
                                  u_int32_t w, u_int32_t h, 
                                  u_int32_t r, u_int32_t c);

/* creates a grid */
MPOS_Grid * MPOS_CreateGrid(int32_t x, int32_t y,
                            u_int32_t w, u_int32_t h, 
                            u_int32_t t_w, u_int32_t t_h);

/* calculates all tiles of given grid */
void MPOS_CalcGrid(MPOS_Grid *grid);

/* sets line color for grid drawing */
void MPOS_SetGridColor(MPOS_Grid *grid, u_int32_t color);

/* draws given grid on given renderer */
void MPOS_DrawGrid(MPOS_Grid *grid, SDL_Renderer *renderer);

/* returns tiles array key in given grid by given position */
int32_t MPOS_GetTileKeyByPos(MPOS_Grid *grid, int32_t x, int32_t y);

/* creates an isometric grid */
MPOS_Grid * MPOS_CreateIsoGrid(int32_t x, int32_t y, 
                               u_int32_t w, u_int32_t h, 
                               u_int32_t t_h);

/* calculates all tiles of given isometric grid */
void MPOS_CalcIsoGrid(MPOS_Grid *grid);

/* draws given isometric grid on given renderer */
void MPOS_DrawIsoGrid(MPOS_Grid *grid, SDL_Renderer *renderer);

/* returns tiles array key in given isometric grid by given position */
int32_t MPOS_GetIsoTileKeyByPos(MPOS_Grid *grid, int32_t x, int32_t y);

/* adds given x and y to each tile rect.x and rect.y in given grid */
void MPOS_MoveGrid(MPOS_Grid *grid, int32_t x, int32_t y);

/* calculates a triangle area */
float MPOS_CalcTriangleArea(float x1, float y1, float x2, float y2, 
                            float x3, float y3);

/* checks if point is in triangle */
uint8_t MPOS_IsPointInTriangle(float x1, float y1, float x2, float y2, 
                               float x3, float y3, float x, float y);

/* returns neighbors of given tile key in given grid */
MPOS_GridTileNeighbors MPOS_GetIsoTileNeighborsByKey(MPOS_Grid *grid, 
                                                     u_int32_t key);

/* calculates isometric tile vector of given grid and tile vector */
MPOS_Vector2 MPOS_GetTileIsoGridVector(MPOS_Grid *grid, MPOS_Vector2 vec);

MPOS_Vector2 MPOS_GetTileIsoGridPos(MPOS_Grid *grid, int32_t x, int32_t y);

/* inverts given matrix */
MPOS_Matrix MPOS_InvertMatrix(MPOS_Matrix matrix);

/* calculates tile vector of given grid and isometric tile vector */
MPOS_Vector2 MPOS_GetTileGridVector(MPOS_Grid *grid, MPOS_Vector2 vec);

MPOS_Vector2 MPOS_GetTileGridPos(MPOS_Grid *grid,  int32_t x, int32_t y);

#endif /* !__MPOS_GRID_H__ */
