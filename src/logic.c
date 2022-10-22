#include "mpos/mpos.h"
#include "logic.h"


void RNV_RunLogic(void)
{
    MPOS_DtFps(app.mpos);

    if (app.state.QUIT == 1)
    {
        /* do things before quitting */
    }
}
