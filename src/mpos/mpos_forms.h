/*
    MPOS_Forms: A module of the mpos library usind the SDL library to provide 
                form and form object handling.
    License:    CC-BY-SA-4.0
*/
#ifndef __MPOS_FORMS_H__
#define __MPOS_FORMS_H__

#include <SDL2/SDL.h>

#include "mpos_sprite.h"

#define MPOS_FORM_STD_BG_COLOR 0x000000;


#ifdef __cplusplus
extern "C" {
#endif

enum MPOS_FormsObjectStates
{
    MPOS_FObj_NORMAL,
    MPOS_FObj_MOUSEHOVER,
    MPOS_FObj_MOUSECLICKED_L,
    MPOS_FObj_MOUSECLICKED_R,
};

typedef struct
{
    SDL_Rect rect;                  /* position and size */
    u_int16_t f_k;                  /* form identifier */
    u_int16_t a_sk;                 /* active sprite key */
    MPOS_Sprite sprite;             /* sprites */
    void (*update)(SDL_Event );     /* object update callback */
} MPOS_FormObj;

typedef struct
{
    SDL_Rect rect;
    SDL_Rect dstrect;
    SDL_Texture *texture;
    SDL_Color bc;                   /* background color */
    MPOS_Sprite b_img;              /* background image */
    u_int16_t o_c;                  /* object counter */
    MPOS_FormObj objs[];            /* form objects */
} MPOS_Form;


MPOS_Form * MPOS_FormCreate(u_int32_t x, u_int32_t y, u_int32_t w, u_int32_t h);

void MPOS_FormAddObject(MPOS_Form **form, MPOS_FormObj *obj);

void MPOS_FormRemoveObject(MPOS_Form **form, MPOS_FormObj *obj);

void MPOS_FormDraw(MPOS_Form *form, SDL_Renderer *r);

void MPOS_FormSetDestRect(MPOS_Form *form, SDL_Rect rect, SDL_Renderer *r);

void MPOS_FormSetBgColor(MPOS_Form *form, u_int32_t color);

void MPOS_FormUpdate(MPOS_Form *form, SDL_Event event);

#ifdef __cplusplus
}
#endif
#endif /* !__MPOS_GRID_H__ */
