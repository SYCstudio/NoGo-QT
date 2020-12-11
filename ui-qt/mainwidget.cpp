#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //initialize buttons and labels
    startNewGameButton = new QPushButton(this);
    loadExistsGameButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    logoWidget = new QWidget(this);
    rightWidget = new QWidget(this);

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

