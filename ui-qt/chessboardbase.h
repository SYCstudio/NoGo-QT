#ifndef CHESSBOARDBASE_H
#define CHESSBOARDBASE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include "chessgrid.h"

class chessboardBase : public QWidget
{
    Q_OBJECT
public:
    explicit chessboardBase(QWidget *parent = nullptr, int size = 50);
    int getTurncnt();
    bool check(int x, int y,int opt = 0);//opt == 0:disable msg prompt;else show msg
    void turncntPlus();

private:
    int boardStatus[9][9], turncnt;
    chessGrid *boardButton[9][9];
    QGridLayout *boardLayout;

    int disableBackup[9][9];

    void disableAllGrid();
    void restoreAllGrid();

signals:
    void turncntChanged();

private slots:
    void click(int opt = 1);
};

#endif // CHESSBOARDBASE_H
