#ifndef CHESSBOARDBASE_H
#define CHESSBOARDBASE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <QSignalMapper>
#include <algorithm>
#include "nogochessboard.h"

class chessboardBase : public QWidget
{
    Q_OBJECT
public:
    explicit chessboardBase(QWidget *parent = nullptr, int size = 50,int show_msg = 1);
    void reset();
    int getTurncnt(){return BoardData -> getTurncnt();}
    void setDisable();
    int isGameEnded(){return BoardData -> isGameEnded();}
    std::vector<int> getBoard(){return BoardData -> getBoard();}
    int check(int x, int y,int show_msg = -1){return BoardData -> check(x, y,show_msg);}
    void place(int x, int y,int show_msg = -1){BoardData -> place(x, y, show_msg);}

private:
    int SHOW_MSG;

    nogochessboard *BoardData;
    QPushButton *BoardButton[9][9];
    QGridLayout *BoardLayout;

signals:
    void gameEnded(int winner);
    void turncntChanged();
    void anyGridClicked();

public slots:
    void clickTrans(int xy);//将 xy 转化为 (x,y) 传递给 BoardData -> place
    void repaintBoard(int turn = -1);
    void undo_buf();
};

#endif // CHESSBOARDBASE_H
