#include "mpos/mpos.h"
#include "utl/media.h"
#include "logic.h"


void RNV_RunLogic(void)
{
    MPOS_DtFps(app.mpos);

    RNV_PlayMusic();

    if (app.state.QUIT == 1)
    {
        /* do things before quitting */
    }
}
