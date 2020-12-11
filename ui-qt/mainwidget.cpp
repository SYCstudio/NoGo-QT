#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //initialize buttons and labels
    startNewGameButton = new QPushButton(this);
    loadExistsGameButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    logoWidget = new QWidget(this);
    rightWidget = new chessboardBase(this, 20);

    startNewGameButton -> setText(tr("New game"));
    loadExistsGameButton -> setText(tr("Load"));
    exitButton -> setText(tr("Exit"));

    //initialzize layout
    mainWindowLayout = new QGridLayout();
    leftButtonLayout = new QVBoxLayout();

    leftButtonLayout -> addWidget(startNewGameButton);
    leftButtonLayout -> addWidget(loadExistsGameButton);
    leftButtonLayout -> addWidget(exitButton);

    mainWindowLayout -> addWidget(logoWidget, 1, 1, 1, 2);
    mainWindowLayout -> addLayout(leftButtonLayout, 2, 1);
    mainWindowLayout -> addWidget(rightWidget, 2, 2);

    setLayout(mainWindowLayout);

    //setup connect
    connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(startNewGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    connect(rightWidget, SIGNAL(gameEnd(int)), this, SLOT(refreshBoard(int)));
    return;
}

mainWidget::~mainWidget()
{
}

void mainWidget::startNewGame()
{
    mainGameWindow *newgame = new mainGameWindow();
    newgame -> show();
    //delete newgame;
    return;
}
void mainWidget::refreshBoard(int opt)
{
    qDebug() << "refresh" ;
    disconnect(rightWidget, SIGNAL(gameEnd(int)), this, SLOT(refreshBoard(int)));

    delete rightWidget;
    rightWidget = new chessboardBase(this, 20);
    mainWindowLayout -> addWidget(rightWidget, 2, 2);
    connect(rightWidget, SIGNAL(gameEnd(int)), this, SLOT(refreshBoard(int)));
    //*/这个地方没有清除 layout 中 rightwidget 的指针就删掉 rightwidget 了，不知道安不安全
    //rightWidget -> chessboardBase(this, 20);
    return;
}
