#include "nogochessboard.h"

nogochessboard::nogochessboard()
{
    memset(Air, 0, sizeof(Air));
    memset(Mark, 0, sizeof(Mark));
    memset(clickX, 0, sizeof(clickX));
    memset(clickY, 0, sizeof(clickY));
    memset(boardStatus, -1, sizeof(boardStatus));
    turncnt = 0;
}
