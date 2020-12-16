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
    explicit chessboardBase(QWidget *parent = nullptr, int size = 50);
    void reset();
    int getTurncnt(){return BoardData -> getTurncnt();}

private:
    nogochessboard *BoardData;
    QPushButton *BoardButton[9][9];
    QGridLayout *BoardLayout;

    void setDisable();
signals:
    void gameEnded(int winner);
    void turncntChanged();

public slots:
    void clickTrans(int xy);//将 xy 转化为 (x,y) 传递给 BoardData -> place
    void repaintBoard(int turn = -1);
};

#endif // CHESSBOARDBASE_H
