/*
    MPOS_Forms: A module of the mpos library usind the SDL library to provide 
                form and form object handling.
    License:    CC-BY-SA-4.0
*/
#include <SDL2/SDL.h>

#include "mpos_forms.h"


MPOS_Form * MPOS_FormCreate(u_int32_t x, u_int32_t y, u_int32_t w, u_int32_t h)
{
    size_t gms = sizeof(MPOS_Form);
    MPOS_Form *form = (MPOS_Form*) malloc(gms);

    if (form != NULL)
    {
        form->o_c = 0;
        form->rect.x = x;
        form->rect.y = y;
        form->rect.w = w;
        form->rect.h = h;

        MPOS_FormSetBgColor(form, MPOS_FORM_STD_BG_COLOR);
    }

    return form;
}

void MPOS_FormAddObject(MPOS_Form **form, MPOS_FormObj *obj)
{
    size_t gms = sizeof(MPOS_Form);
    gms += ((*form)->o_c + 1) * sizeof(MPOS_FormObj);
    *form = (MPOS_Form*) realloc(*form, gms);

    if (form != NULL)
    {
        (*form)->objs[(*form)->o_c].f_k = (*form)->o_c;
        (*form)->objs[(*form)->o_c].a_sk = MPOS_FObj_NORMAL;
        (*form)->objs[(*form)->o_c].rect = obj->rect;
        (*form)->objs[(*form)->o_c].sprite = obj->sprite;
        (*form)->objs[(*form)->o_c].update = obj->update;

        (*form)->o_c++;
    }
}

void MPOS_FormRemoveObject(MPOS_Form **form, MPOS_FormObj *obj)
{
    int32_t ak = -1;

    for (size_t i = 0; i < (*form)->o_c; i++)
    {
        if ((*form)->objs[i].f_k == i)
        {
            ak = i;
            break;
        }
    }

    if (ak == -1)
    {
        return;
    }

    for (size_t j = ak; j < (*form)->o_c - 1; j++)
    {
        (*form)->objs[(*form)->o_c].f_k = j;
        (*form)->objs[(*form)->o_c].a_sk = (*form)->objs[j + 1].a_sk;
        (*form)->objs[(*form)->o_c].rect = (*form)->objs[j + 1].rect;
        (*form)->objs[(*form)->o_c].sprite = (*form)->objs[j + 1].sprite;
        (*form)->objs[(*form)->o_c].update = (*form)->objs[j + 1].update;
    }
    (*form)->o_c--;

    size_t gms = sizeof(MPOS_Form);
    gms += (*form)->o_c * sizeof(MPOS_FormObj);
    *form = (MPOS_Form*) realloc(*form, gms);
}

void MPOS_FormDraw(MPOS_Form *form, SDL_Renderer *r)
{
    if (form->texture == NULL)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "[MPOS Form] No destination set. Use %s to set it.",
                    "MPOS_FormSetDestRect");
        return;
    }

    SDL_SetRenderTarget(r, form->texture);
    SDL_SetRenderDrawColor(r, form->bc.r, form->bc.g, form->bc.b, form->bc.a);
    SDL_RenderClear(r);

    if (form->o_c > 0)
    {
        for (size_t i = 0; i < form->o_c; i++)
        {
            MPOS_SpriteDraw(form->objs[i].sprite, r);
        }
    }

    SDL_SetRenderTarget(r, NULL);

    SDL_Rect srcrect = (SDL_Rect){0, 0, form->dstrect.w, form->dstrect.h};
    SDL_RenderCopy(r, form->texture, &srcrect, &form->dstrect);
}

void MPOS_FormSetDestRect(MPOS_Form *form, SDL_Rect rect, SDL_Renderer *r)
{
    form->dstrect.x = rect.x;
    form->dstrect.y = rect.y;
    form->dstrect.w = rect.w;
    form->dstrect.h = rect.h;

    form->texture = SDL_CreateTexture(r,
                                      SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET,
                                      form->dstrect.w,
                                      form->dstrect.h);
}

void MPOS_FormSetBgColor(MPOS_Form *form, u_int32_t color)
{
    u_int8_t r = color & 0xff;
    u_int8_t g = (color>>8) & 0xff;
    u_int8_t b = (color>>16) & 0xff;
    u_int8_t a = 0xff;

    form->bc = (SDL_Color) { r, g, b, a };
}

void MPOS_FormUpdate(MPOS_Form *form, SDL_Event event)
{
    if (form->o_c > 0)
    {
        for (size_t i = 0; i < form->o_c; i++)
        {
            if (form->objs[i].update != NULL)
            {
                form->objs[i].update(event);
            }
        }
    }
}
