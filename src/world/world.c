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
        case SDLK_F2:
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

    switch (world->states.MOVE)
    {
    case RNV_WORLD_MOVE_UP:
        move_y = RNV_WORLD_MOVE_SPEED;
        move_x = RNV_WORLD_MOVE_SPEED;
        break;
    case RNV_WORLD_MOVE_DOWN:
        move_y = -RNV_WORLD_MOVE_SPEED;
        move_x = -RNV_WORLD_MOVE_SPEED;
        break;
    case RNV_WORLD_MOVE_LEFT:
        move_y = -RNV_WORLD_MOVE_SPEED;
        move_x = RNV_WORLD_MOVE_SPEED;
        break;
    case RNV_WORLD_MOVE_RIGHT:
        move_y = RNV_WORLD_MOVE_SPEED;
        move_x = -RNV_WORLD_MOVE_SPEED;
        break;
    case RNV_WORLD_MOVE_TL:
        move_x = RNV_WORLD_MOVE_SPEED;
        break;
    case RNV_WORLD_MOVE_TR:
        move_y = RNV_WORLD_MOVE_SPEED;
        break;
    case RNV_WORLD_MOVE_BL:
        move_y = -RNV_WORLD_MOVE_SPEED;
        break;
    case RNV_WORLD_MOVE_BR:
        move_x = -RNV_WORLD_MOVE_SPEED;
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
        if (world->map[i].layer.terrain.sh != NULL)
        {
            MPOS_SpriteUpdate(&world->map[i].layer.terrain);
        }
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
        /* calculate iso rect */
        int32_t x = world->map[i].layer.terrain.rect.x;
        int32_t y = world->map[i].layer.terrain.rect.y;
        MPOS_Vector2 spr = MPOS_GetTileIsoGridPos(world->grid, x, y);
        world->map[i].layer.terrain.iso_rect.x = spr.x;
        world->map[i].layer.terrain.iso_rect.y = spr.y;
        world->map[i].layer.terrain.iso_rect.w = RNV_WORLD_TILE_WIDTH;
        world->map[i].layer.terrain.iso_rect.h = RNV_WORLD_TILE_HEIGHT;

        /* check for layer */
        if (world->map[i].layer.terrain.sh != NULL)
            MPOS_SpriteDrawIso(world->map[i].layer.terrain, r);
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
