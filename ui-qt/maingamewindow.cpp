#include "maingamewindow.h"

mainGameWindow::mainGameWindow(QWidget *parent) : QWidget(parent)
{
    //initialize labels and buttons.
    timePrompt = new QLabel();
    timeShow = new QLabel();
    timePrompt -> setText(tr("Time:"));

    turnPrompt = new QLabel();
    turnShow = new QLabel();
    turnPrompt -> setText(tr("Turn:"));

    saveButton = new QPushButton();
    saveButton -> setText(tr("Save"));

    quitButton = new QPushButton();
    quitButton -> setText(tr("Quit"));

    for (int i = 0; i < 81; i++) {
        historyButtons[i] = new QPushButton();
        historyButtons[i] -> setFixedSize(10,50);
        historyButtons[i] -> setEnabled(0);
    }

    chessBoard = new chessboardBase();

    //initialize layout
    rightLayout = new QGridLayout();
    rightLayout -> addWidget(timePrompt, 1, 1);
    rightLayout -> addWidget(timeShow, 1, 2);
    rightLayout -> addWidget(turnPrompt, 2, 1);
    rightLayout -> addWidget(turnShow, 2, 2);
    rightLayout -> addWidget(saveButton, 3, 1, 1, 2);
    rightLayout -> addWidget(quitButton, 4, 1, 1, 2);

    bottomLayout = new QHBoxLayout();
    bottomLayout -> setSpacing(0);
    for (int i = 0; i < 81; i++) bottomLayout -> addWidget(historyButtons[i]);

    mainLayout = new QGridLayout();
    mainLayout -> addWidget(chessBoard, 1, 1);
    mainLayout -> addLayout(rightLayout, 1, 2);
    mainLayout -> addLayout(bottomLayout, 2, 1, 1, 2);

    setLayout(mainLayout);

    //setup connect
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(chessBoard, SIGNAL(turncntChanged()), this, SLOT(turnShowRefresh()));

    return;
}

void mainGameWindow::turnShowRefresh()
{
    //qDebug() << "get-in turnShowRefresh";
    turnShow -> setText(QString("%1").arg(chessBoard -> getTurncnt()));
    //turnPrompt -> setText(QString("%1").arg(chessBoard -> getTurncnt()));
    return;
}
