#ifndef IOINTERACTOR_H
#define IOINTERACTOR_H

#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QEventLoop>
#include "maingamewindow.h"
#include "aiheader.h"

class ioInteractor : public QWidget
{
    Q_OBJECT
public:
    ioInteractor(int _Player, mainGameWindow *buf = nullptr);
    void startGame();
private:
    int Player[2], WINNER, AI_ID;
    mainGameWindow *Game;
    aimodule *AI[2];

public slots:
    void aiMove();
    void write(QString filename);
};

#endif // IOINTERACTOR_H
