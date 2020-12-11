#include "chessgrid.h"

chessGrid::chessGrid(QWidget *parent) : QPushButton(parent)
{

}

void chessGrid::setMark(int opt)
{
    mark = opt;
    return;
}
