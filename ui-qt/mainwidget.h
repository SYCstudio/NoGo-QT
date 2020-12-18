#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>
#include "maingamewindow.h"
#include "chessboardbase.h"
#include "playerselecter.h"
#include "iointeractor.h"

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    QPushButton *StartNewGameButton;
    QPushButton *LoadExistsGameButton;
    QPushButton *ExitButton;
    QGridLayout *MainWindowLayout;
    QVBoxLayout *LeftButtonLayout;
    QWidget *LogoWidget;//logo placeHolder
    chessboardBase *Chessboard;

private slots:
    void startNewGame();
    void refreshBoard(int opt);
};
#endif // MAINWIDGET_H
