#include "chessboardbase.h"

chessboardBase::chessboardBase(QWidget *parent,int size) : QWidget(parent)
{
    //initialize buttons and labels
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            boardButton[i][j] = new QPushButton();
            boardButton[i][j] -> setFixedSize(size, size);
        }

    //initialize layout;
    boardLayout = new QGridLayout();
    boardLayout -> setSpacing(0);
    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) boardLayout -> addWidget(boardButton[i][j], i, j);
    setLayout(boardLayout);

    return;
}
