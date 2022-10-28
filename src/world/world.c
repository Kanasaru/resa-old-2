#include <SDL2/SDL.h>

#include "oab.h"
#include "world.h"

extern App app;


void RNV_WorldHandleEvent(RNV_World *world, SDL_Event event)
{
    switch (event.type)
    {
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_F3:
            if (world->states.SHOW_GRID)
            {
                world->states.SHOW_GRID = 0;
            }
            else
            {
                world->states.SHOW_GRID = 1;
            }
            break;
        case SDLK_UP:
            world->states.MOVE = RNV_WORLD_MOVE_UP ^ world->states.MOVE;
            break;
        case SDLK_DOWN:
            world->states.MOVE = RNV_WORLD_MOVE_DOWN ^ world->states.MOVE;
            break;
        case SDLK_LEFT:
            world->states.MOVE = RNV_WORLD_MOVE_LEFT ^ world->states.MOVE;
            break;
        case SDLK_RIGHT:
            world->states.MOVE = RNV_WORLD_MOVE_RIGHT ^ world->states.MOVE;
            break;
        }
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            world->states.MOVE = world->states.MOVE | RNV_WORLD_MOVE_UP;
            break;
        case SDLK_DOWN:
            world->states.MOVE = world->states.MOVE | RNV_WORLD_MOVE_DOWN;
            break;
        case SDLK_LEFT:
            world->states.MOVE = world->states.MOVE | RNV_WORLD_MOVE_LEFT;
            break;
        case SDLK_RIGHT:
            world->states.MOVE = world->states.MOVE | RNV_WORLD_MOVE_RIGHT;
            break;
        }
    }
}

void RNV_WorldMove(RNV_World *world)
{
    int move_x = 0;
    int move_y = 0;

    int px_right = world->rect.w - world->dstrect.w - abs(0 - world->rect.x);
    int px_left = abs(0 - world->rect.x);
    int px_up = abs(0 - world->rect.y);
    int px_down = world->rect.h - world->dstrect.h - abs(0 - world->rect.y);

    switch (world->states.MOVE)
    {
    case RNV_WORLD_MOVE_UP:
        if (px_up != 0)
        {
            if (px_up < RNV_WORLD_MOVE_SPEED)
                move_y = px_up;
            else
                move_y = RNV_WORLD_MOVE_SPEED;
        }
        break;
    case RNV_WORLD_MOVE_DOWN:
        if (px_down != 0)
        {
            if (px_down < RNV_WORLD_MOVE_SPEED)
                move_y = -px_down;
            else
                move_y = -RNV_WORLD_MOVE_SPEED;
        }
        break;
    case RNV_WORLD_MOVE_LEFT:
        if (px_left != 0)
        {
            if (px_left < RNV_WORLD_MOVE_SPEED)
                move_x = px_left;
            else
                move_x = RNV_WORLD_MOVE_SPEED;
        }
        break;
    case RNV_WORLD_MOVE_RIGHT:
        if (px_right != 0)
        {
            if (px_right < RNV_WORLD_MOVE_SPEED)
                move_x = -px_right;
            else
                move_x = -RNV_WORLD_MOVE_SPEED;
        }
        break;
    case RNV_WORLD_MOVE_TL:
        if (px_up != 0)
        {
            if (px_up < RNV_WORLD_MOVE_SPEED)
                move_y = px_up;
            else
                move_y = RNV_WORLD_MOVE_SPEED;
        }
        if (px_left != 0)
        {
            if (px_left < RNV_WORLD_MOVE_SPEED)
                move_x = px_left;
            else
                move_x = RNV_WORLD_MOVE_SPEED;
        }
        break;
    case RNV_WORLD_MOVE_TR:
        if (px_up != 0)
        {
            if (px_up < RNV_WORLD_MOVE_SPEED)
                move_y = px_up;
            else
                move_y = RNV_WORLD_MOVE_SPEED;
        }
        if (px_right != 0)
        {
            if (px_right < RNV_WORLD_MOVE_SPEED)
                move_x = -px_right;
            else
                move_x = -RNV_WORLD_MOVE_SPEED;
        }
        break;
    case RNV_WORLD_MOVE_BL:
        if (px_down != 0)
        {
            if (px_down < RNV_WORLD_MOVE_SPEED)
                move_y = -px_down;
            else
                move_y = -RNV_WORLD_MOVE_SPEED;
        }
        if (px_left != 0)
        {
            if (px_left < RNV_WORLD_MOVE_SPEED)
                move_x = px_left;
            else
                move_x = RNV_WORLD_MOVE_SPEED;
        }
        break;
    case RNV_WORLD_MOVE_BR:
        if (px_down != 0)
        {
            if (px_down < RNV_WORLD_MOVE_SPEED)
                move_y = -px_down;
            else
                move_y = -RNV_WORLD_MOVE_SPEED;
        }
        if (px_right != 0)
        {
            if (px_right < RNV_WORLD_MOVE_SPEED)
                move_x = -px_right;
            else
                move_x = -RNV_WORLD_MOVE_SPEED;
        }
        break;
    }

    if (move_x != 0 || move_y != 0)
    {
        MPOS_MoveGrid(world->grid, move_x, move_y);
        world->rect.x += move_x;
        world->rect.y += move_y;
    }
}

void RNV_WorldUpdate(RNV_World *world)
{
    if (world->states.MOVE != RNV_WORLD_MOVE_NO)
    {
        RNV_WorldMove(world);
    }

    for (int i = 0; i < world->grid->t_c; i++)
    {
        MPOS_SpriteUpdate(&world->map[i].layer.terrain);
    }
}

void RNV_WorldDraw(RNV_World *world, SDL_Renderer *r)
{
    if (world->texture == NULL)
    {
        return;
    }

    SDL_SetRenderTarget(r, world->texture);
    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(r);

    for (size_t i = 0; i < world->grid->t_c; i++)
    {
        /* only draw sprite if visibile */
        if (world->map[i].rect->x + world->map[i].rect->h >= 0 ||
            world->map[i].rect->x <= world->rect.w ||
            world->map[i].rect->y + world->map[i].rect->h >= 0 ||
            world->map[i].rect->y <= world->rect.h)
        {
            MPOS_SpriteDraw(world->map[i].layer.terrain, r);
        }
    }

    if (world->states.SHOW_GRID)
    {
        MPOS_DrawGrid(world->grid, r);
    }

    SDL_SetRenderTarget(r, NULL);

    SDL_Rect srcrect = (SDL_Rect){0, 0, world->dstrect.w, world->dstrect.h};
    SDL_RenderCopy(r, world->texture, &srcrect, &world->dstrect);
}

void RNV_WorldSetRenderRect(RNV_World *world, SDL_Rect rect)
{
    world->dstrect.x = rect.x;
    world->dstrect.y = rect.y;
    world->dstrect.w = rect.w;
    world->dstrect.h = rect.h;

    world->texture = SDL_CreateTexture(app.renderer,
                                       SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET,
                                       world->dstrect.w,
                                       world->dstrect.h);
}
