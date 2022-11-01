/*
    MPOS_Grid: A module of the mpos library usind the SDL library to provide 
               basic grid and isometric grid handling.
    License:   CC-BY-SA-4.0
*/
#include <SDL2/SDL.h>

#include "mpos_grid.h"


const float MPOS_Grid_i_x = 1;
const float MPOS_Grid_i_y = 0.5;
const float MPOS_Grid_j_x = -1;
const float MPOS_Grid_j_y = 0.5;

MPOS_GridTile MPOS_CreateGridTile(u_int32_t k, int32_t x, int32_t y, 
                                  u_int32_t w, u_int32_t h, 
                                  u_int32_t r, u_int32_t c)
{
    MPOS_GridTile tile;

    tile.key  = k;
    tile.row  = r;
    tile.col  = c;
    tile.rect = (SDL_Rect) { x, y, w, h };

    return tile;
}

MPOS_Grid * MPOS_CreateGrid(int32_t x, int32_t y,
                            u_int32_t w, u_int32_t h, 
                            u_int32_t t_w, u_int32_t t_h)
{
    size_t gms = sizeof(MPOS_Grid) + w * h * sizeof(MPOS_GridTile);
    MPOS_Grid *grid = (MPOS_Grid*) malloc(gms);

    if (grid != NULL)
    {
        grid->rect  = (SDL_Rect) { x, y, w, h };
        grid->t_w   = t_w;
        grid->t_h   = t_h;
        grid->t_c   = w * h;
        grid->c     = (SDL_Color) { 255, 255, 255, 255 };
    }

    MPOS_CalcGrid(grid);

    return grid;
}

void MPOS_CalcGrid(MPOS_Grid *grid)
{
    uint32_t key = 0;
    for (uint32_t row = 0; row < grid->rect.h; row++)
    {
        for (uint32_t col = 0; col < grid->rect.w; col++)
        {
            int32_t x = col * grid->t_w;
            int32_t y = row * grid->t_h;
            grid->tiles[key] = MPOS_CreateGridTile(key, x, y, 
                                                   grid->t_w, grid->t_h, 
                                                   row, col);
            key++;
        }
    }
}

void MPOS_SetGridColor(MPOS_Grid *grid, u_int32_t color)
{
    u_int8_t r = color & 0xff;
    u_int8_t g = (color>>8) & 0xff;
    u_int8_t b = (color>>16) & 0xff;
    u_int8_t a = 0xff;

    grid->c = (SDL_Color) { r, g, b, a };
}

void MPOS_DrawGrid(MPOS_Grid *grid, SDL_Renderer *r)
{
    SDL_SetRenderDrawColor(r, grid->c.r, grid->c.g, grid->c.b, grid->c.a);
    for (size_t i = 0; i < grid->rect.w * grid->rect.h; i++)
    {
        SDL_RenderDrawRect(r, &grid->tiles[i].rect);
    }
}

int32_t MPOS_GetTileKeyByPos(MPOS_Grid *grid, int32_t x, int32_t y)
{
    uint32_t col = (uint32_t) (x / grid->t_w);
    uint32_t row = (uint32_t) (y / grid->t_h);

    if (row < grid->rect.h && col < grid->rect.w )
    {
        uint32_t key = row * grid->rect.w + col;
        return key;
    }

    return -1;
}

MPOS_Grid * MPOS_CreateIsoGrid(int32_t x, int32_t y, 
                               u_int32_t w, u_int32_t h, 
                               u_int32_t t_h)
{
    size_t gms = sizeof(MPOS_Grid);
    uint32_t keys = 0;
    for (size_t row_nb = 0; row_nb < h; row_nb++)
    {
        keys += w / 2;
        if (row_nb < h - 1)
            keys += w / 2 - 1;
    }
    gms += keys * sizeof(MPOS_GridTile);
    MPOS_Grid *grid = (MPOS_Grid*) malloc(gms);

    if (grid != NULL)
    {
        grid->rect = (SDL_Rect) { x, y, w, h };
        grid->t_w  = t_h * 2;
        grid->t_h  = t_h;
        grid->t_c  = keys;
        grid->c    = (SDL_Color) { 255, 255, 255, 255 };
    }

    MPOS_CalcIsoGrid(grid);

    return grid;
}

void MPOS_CalcIsoGrid(MPOS_Grid *grid)
{
    uint32_t key = 0;
    uint32_t row = 0;
    uint32_t col = 0;
    int32_t y = 0;
    int32_t x = 0;

    for (size_t row_nb = 0; row_nb < grid->rect.h; row_nb++)
    {
        for (size_t col_nb = 0; col_nb < grid->rect.w / 2; col_nb++)
        {
            x = col_nb * grid->t_w;
            y = grid->t_h * row_nb;
            grid->tiles[key] = MPOS_CreateGridTile(key, x, y, 
                                                    grid->t_w, grid->t_h, 
                                                    row, col);
            key++;
        }
        if (row_nb < grid->rect.h - 1)
        {
            row++;
            col = 0;
            x = -grid->t_w / 2;
            y += grid->t_h / 2;
            for (size_t hl = 0; hl < (grid->rect.w / 2 - 1); hl++)
            {
                x += grid->t_w;
                grid->tiles[key] = MPOS_CreateGridTile(key, x, y, 
                                                        grid->t_w, grid->t_h, 
                                                        row, col);
                key++;
                col++;
            }
            
        }
        row++;
    }
}

void MPOS_DrawIsoGrid(MPOS_Grid *grid, SDL_Renderer *r)
{
    SDL_SetRenderDrawColor(r, grid->c.r, grid->c.g, grid->c.b, grid->c.a);
    for (int32_t r_nb = 0; r_nb < grid->rect.h; r_nb++)
    {
        for (int32_t c_nb = 0; c_nb < grid->rect.w / 2; c_nb++)
        {
            int32_t lx = c_nb * grid->t_w;
            int32_t ly = (grid->t_h / 2) * (r_nb * 2 + 1);
            int32_t tx = grid->t_w / 2 + c_nb * grid->t_w;
            int32_t ty = grid->t_h * r_nb;
            int32_t rx = (c_nb + 1) * grid->t_w;
            int32_t ry = (grid->t_h / 2) * (r_nb * 2 + 1);
            int32_t bx = grid->t_w / 2 + c_nb * grid->t_w;
            int32_t by = grid->t_h * (r_nb + 1);

            lx += grid->tiles[0].rect.x;
            ly += grid->tiles[0].rect.y;
            tx += grid->tiles[0].rect.x;
            ty += grid->tiles[0].rect.y;
            rx += grid->tiles[0].rect.x;
            ry += grid->tiles[0].rect.y;
            bx += grid->tiles[0].rect.x;
            by += grid->tiles[0].rect.y;

            SDL_RenderDrawLine(r, lx, ly - 1, tx - 1, ty);
            SDL_RenderDrawLine(r, tx, ty, rx - 1, ry - 1);
            SDL_RenderDrawLine(r, lx, ly, bx - 1, by - 1);
            SDL_RenderDrawLine(r, bx, by - 1, rx - 1, ry);
        }
    }
}

int32_t MPOS_GetIsoTileKeyByPos(MPOS_Grid *grid, int32_t x, int32_t y)
{
    if (x > grid->rect.w * grid->t_w / 2 || y > grid->rect.h * grid->t_h)
        return -1;

    int32_t c = (int32_t) (x / (grid->t_w / 2));
    int32_t r = (int32_t) (y / grid->t_h);

    int32_t x1   = c * grid->t_w / 2;
    int32_t y1   = r * grid->t_h;
    int32_t x2   = (c + 1) * grid->t_w / 2 - 1;
    int32_t y2   = r * grid->t_h;
    int32_t x3_1 = c * grid->t_w / 2;
    int32_t x3_2 = (c + 1) * grid->t_w / 2;
    int32_t y3   = (r + 1) * grid->t_h / 2 - 1 + (r * grid->t_h / 2);
    int32_t x4   = c * grid->t_w / 2;
    int32_t y4   = (r + 1) * grid->t_h - 1;
    int32_t x5   = (c + 1) * grid->t_w / 2 - 1;
    int32_t y5   = (r + 1) * grid->t_h - 1;

    int32_t i_c  = c / 2;
    int32_t r_w  = r * (grid->rect.w / 2 - 1);
    int32_t i_k  = i_c + r * grid->rect.w / 2 + r_w;
    int32_t k_tl = i_c + (r - 1) * grid->rect.w / 2 + r_w;
    int32_t k_tr = i_c + (r - 1) * grid->rect.w / 2 + r_w + 1;
    int32_t k_bl = i_c + (r + 1) * grid->rect.w / 2 + r_w - 1;
    int32_t k_br = i_c + (r + 1) * grid->rect.w / 2 + r_w;

    if (c % 2 == 0)
    {
        if (MPOS_IsPointInTriangle(x1, y1, x2, y2, x3_1, y3, x, y))
        {
            if (x < grid->t_w / 2 || y < grid->t_h / 2)
            {
                return -1;
            }
            i_k = k_tl;
        }
        else if (MPOS_IsPointInTriangle(x3_1, y3 + 1, x4, y4, x5, y5, x, y))
        {
            if (x < grid->t_w / 2 || 
                (grid->rect.h * grid->t_h - y) < grid->t_h / 2)
            {
                return -1;
            }
            i_k = k_bl;
        }
    }
    else
    {
        if (MPOS_IsPointInTriangle(x1, y1, x2, y2, x3_2, y3, x, y))
        {
            if ((grid->rect.w * grid->t_w / 2 - x) < grid->t_w / 2 || 
                y < grid->t_h / 2)
            {
                return -1;
            }
            i_k = k_tr;
        }
        else if (MPOS_IsPointInTriangle(x3_2, y3 + 1, x4, y4, x5, y5, x, y))
        {
            if ((grid->rect.w * grid->t_w / 2 - x) < grid->t_w / 2 || 
                (grid->rect.h * grid->t_h - y) < grid->t_h / 2)
            {
                return -1;
            }
            i_k = k_br;
        }
    }

    return i_k;
}

void MPOS_MoveGrid(MPOS_Grid *grid, int32_t x, int32_t y)
{
    for (size_t i = 0; i < grid->t_c; i++)
    {
        grid->tiles[i].rect.x += x;
        grid->tiles[i].rect.y += y;
    }
}

float MPOS_CalcTriangleArea(float x1, float y1, float x2, float y2, 
                            float x3, float y3)
{
    return fabs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

uint8_t MPOS_IsPointInTriangle(float x1, float y1, float x2, float y2, 
                               float x3, float y3, float x, float y)
{
    float a  = MPOS_CalcTriangleArea(x1, y1, x2, y2, x3, y3);
    float a1 = MPOS_CalcTriangleArea(x, y, x2, y2, x3, y3);
    float a2 = MPOS_CalcTriangleArea(x1, y1, x, y, x3, y3);
    float a3 = MPOS_CalcTriangleArea(x1, y1, x2, y2, x, y);

    if (a == a1 + a2 + a3)
        return 1;

    return 0;
}

MPOS_GridTileNeighbors MPOS_GetIsoTileNeighborsByKey(MPOS_Grid *grid, 
                                                     u_int32_t key)
{
    MPOS_GridTileNeighbors nb;

    nb.l  = key - 1;
    nb.r  = key + 1;
    nb.t  = key - (grid->rect.w / 2) * 2 + 1;
    nb.b  = key + (grid->rect.w / 2) * 2 - 1;
    nb.tl = key - grid->rect.w / 2;
    nb.tr = key - grid->rect.w / 2 + 1;
    nb.bl = key + grid->rect.w / 2 - 1;
    nb.br = key + grid->rect.w / 2;

    if (grid->tiles[key].col == 0 && grid->tiles[key].row % 2 == 0)
    {
        nb.l = -1;
        nb.tl = -1;
        nb.bl = -1;
    }
    if (grid->tiles[key].col == 0 && grid->tiles[key].row % 2 != 0)
    {
        nb.l = -1;
    }
    if (grid->tiles[key].col == grid->rect.w / 2 - 1 && 
        grid->tiles[key].row % 2 == 0)
    {
        nb.r = -1;
        nb.tr = -1;
        nb.br = -1;
    }
    if (grid->tiles[key].col == grid->rect.w / 2 - 2 && 
        grid->tiles[key].row % 2 != 0)
    {
        nb.r = -1;
    }
    if (nb.b > grid->t_c)
    {
        nb.b = -1;
    }
    if (nb.bl > grid->t_c)
    {
        nb.bl = -1;
    }
    if (nb.br > grid->t_c)
    {
        nb.br = -1;
    }

    return nb;
}

MPOS_Vector2 MPOS_GetTileIsoGridVector(MPOS_Grid *grid, MPOS_Vector2 vec)
{
    MPOS_Vector2 iso;

    iso.x = vec.x * MPOS_Grid_i_x * 0.5 * grid->t_w + 
            vec.y * MPOS_Grid_j_x * 0.5 * grid->t_w;
    iso.y = vec.x * MPOS_Grid_i_y * 0.5 * grid->t_h + 
            vec.y * MPOS_Grid_j_y * 0.5 * grid->t_h;

    return iso;
}

MPOS_Matrix MPOS_InvertMatrix(MPOS_Matrix matrix)
{
    MPOS_Matrix inv;
    float det = (1 / (matrix.a * matrix.d - matrix.b * matrix.c));

    inv.a = det * matrix.d;
    inv.b = det * -matrix.b;
    inv.c = det * -matrix.c;
    inv.d = det * matrix.a;

    return inv;
}

MPOS_Vector2 MPOS_GetTileGridVector(MPOS_Grid *grid, MPOS_Vector2 vec)
{
    MPOS_Matrix mat;
    MPOS_Matrix inv;
    MPOS_Vector2 gvec;

    mat.a = MPOS_Grid_i_x * 0.5 * grid->t_w;
    mat.b = MPOS_Grid_j_x * 0.5 * grid->t_w;
    mat.c = MPOS_Grid_i_y * 0.5 * grid->t_h;
    mat.d = MPOS_Grid_j_y * 0.5 * grid->t_h;
  
    inv = MPOS_InvertMatrix(mat);
  
    gvec.x = vec.x * inv.a + vec.y * inv.b;
    gvec.y = vec.x * inv.c + vec.y * inv.d;

    return gvec;
}
