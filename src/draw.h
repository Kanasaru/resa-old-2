#ifndef __RNV_DRAW_H__
#define __RNV_DRAW_H__

#include "oab.h"


extern App app;

/* handles all drawing and calls to drawing functions */
void RNV_Draw(void);

/* prepares the screen for drawing */
void RNV_PrepareScreen(void);

/* switches surfaces */
void RNV_PresentScreen(void);

/* draws game/debug panel */
void RNV_DrawPanel(void);

#endif /* !__RNV_DRAW_H__ */
