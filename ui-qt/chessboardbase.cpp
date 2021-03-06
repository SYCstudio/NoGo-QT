#include "chessboardbase.h"

chessboardBase::chessboardBase(QWidget *parent,int size,int show_msg) : QWidget(parent)
{
    SHOW_MSG = show_msg;
    is_tips_showed = 0;
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
    BoardData = new nogochessboard(nullptr, SHOW_MSG);

    //initialize connect
    //连接按钮触发与内联棋盘数据
    QSignalMapper *mapForBoard = new QSignalMapper();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            connect(BoardButton[i][j], SIGNAL(clicked()), mapForBoard, SLOT(map()));
            connect(BoardButton[i][j], SIGNAL(clicked()), this, SIGNAL(anyGridClicked()));
        }
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
            //BoardButton[i][j] -> setStyleSheet("");
        }
    return;
}

void chessboardBase::repaintBoard(int turn) {
    setDisable();
    if (turn == -1) turn = BoardData -> getTurncnt();
    //qDebug() << turn;
    std::vector<std::pair<int, int> > R = BoardData -> getBoard(turn);
    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) BoardButton[i][j] -> setStyleSheet("");
    for (int i = 0; i < turn; i++)
        if (i & 1) BoardButton[R[i].first][R[i].second] -> setStyleSheet("background-color: white");
        else BoardButton[R[i].first][R[i].second] -> setStyleSheet("background-color: black");
    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) BoardButton[i][j] -> setEnabled(turn == BoardData -> getTurncnt());
    //qDebug() << is_tips_showed;
    if (is_tips_showed) showTips();
    return;
}

void chessboardBase::clickTrans(int xy) {
    //qDebug() << "click:" << xy;
    setDisable();
    BoardData -> place(xy / 9, xy % 9);
    repaintBoard();
    return;
}

void chessboardBase::undo_buf() {
    BoardData -> undo();
    repaintBoard();
    return;
}

void chessboardBase::showTips()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            //if (BoardButton[i][j] -> isEnabled() == 0) continue;
            if (BoardData -> check(i, j, 0) == -1) {
                BoardButton[i][j] -> setEnabled(0);
                BoardButton[i][j] -> setStyleSheet("background-color: Lightpink");
            }
            else if (BoardData -> checkopp(i, j) == -1) {
                BoardButton[i][j] -> setStyleSheet("background-color: Aquamarine");
            }
        }
    return;
}

void chessboardBase::changeshowTipsFlag()
{
    //qDebug() << "switch";
    is_tips_showed ^= 1;
    repaintBoard();
    //qDebug() << is_tips_showed;
    return;
}
