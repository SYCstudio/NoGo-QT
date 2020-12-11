#include "chessgrid.h"

chessGrid::chessGrid(QWidget *parent) : QPushButton(parent)
{
    mark = 0;
    return;
}

void chessGrid::setMark(int opt)
{
    mark = opt;
    return;
}

int chessGrid::getMark()
{
    return mark;
}
