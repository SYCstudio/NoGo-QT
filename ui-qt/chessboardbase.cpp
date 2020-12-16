#include "chessboardbase.h"

chessboardBase::chessboardBase(QWidget *parent,int size) : QWidget(parent)
{
    //initialize buttons and labels
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            BoardButton[i][j] = new QPushButton();
            BoardButton[i][j] -> setFixedSize(size, size);
        }

    //initialize layout;
    BoardLayout = new QGridLayout();
    BoardLayout -> setSpacing(0);
    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) BoardLayout -> addWidget(BoardButton[i][j], i, j);
    setLayout(BoardLayout);

    //initialize boarddata
    BoardData = new nogochessboard();

    //initialize connect
    //连接按钮触发与内联棋盘数据
    QSignalMapper *mapForBoard = new QSignalMapper();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            connect(BoardButton[i][j], SIGNAL(clicked()), mapForBoard, SLOT(map()));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            mapForBoard -> setMapping(BoardButton[i][j], i*9+j);
    connect(mapForBoard, SIGNAL(mapped(int)), this, SLOT(clickTrans(int)));

    connect(BoardData, SIGNAL(gameEnded(int)), this, SIGNAL(gameEnded(int)));
    connect(BoardData, SIGNAL(turncntChanged()), this, SIGNAL(turncntChanged()));
    return;
}

void chessboardBase::reset() {
    //initialize buttons and labels
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            BoardButton[i][j] -> setStyleSheet("");
        }

    //initialize boarddata
    BoardData -> reset();
    repaintBoard();
    return;
}

void chessboardBase::setDisable() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            BoardButton[i][j] -> setEnabled(0);
            BoardButton[i][j] -> setStyleSheet("");
        }
    return;
}

void chessboardBase::repaintBoard(int turn) {
    setDisable();
    if (turn == -1) turn = BoardData -> getTurncnt();
    //qDebug() << turn;
    std::vector<int> Bd = BoardData -> getBoard(turn);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            int col = Bd[i * 9 + j];
            if (col == 0) BoardButton[i][j] -> setStyleSheet("background-color: white");
            if (col == 1) BoardButton[i][j] -> setStyleSheet("background-color: black");
        }
    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) BoardButton[i][j] -> setEnabled(turn == BoardData -> getTurncnt());
    return;
}

void chessboardBase::clickTrans(int xy) {
    setDisable();
    BoardData -> place(xy / 9, xy % 9);
    repaintBoard();
    return;
}
