#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QApplication>
#include "maingamewindow.h"
#include "chessboardbase.h"

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    QPushButton *startNewGameButton;
    QPushButton *loadExistsGameButton;
    QPushButton *exitButton;
    QGridLayout *mainWindowLayout;
    QVBoxLayout *leftButtonLayout;
    QWidget *logoWidget;//logo placeHolder
    chessboardBase *rightWidget;

private slots:
    void startNewGame();
};
#endif // MAINWIDGET_H
