#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //initialize buttons and labels
    StartNewGameButton = new QPushButton();
    LoadExistsGameButton = new QPushButton();
    ExitButton = new QPushButton();
    LogoWidget = new QWidget();
    Chessboard = new chessboardBase(nullptr, 20, 0);

    StartNewGameButton -> setText(tr("New game"));
    LoadExistsGameButton -> setText(tr("Load"));
    ExitButton -> setText(tr("Exit"));

    //initialzize layout
    MainWindowLayout = new QGridLayout();
    LeftButtonLayout = new QVBoxLayout();

    LeftButtonLayout -> addWidget(StartNewGameButton);
    LeftButtonLayout -> addWidget(LoadExistsGameButton);
    LeftButtonLayout -> addWidget(ExitButton);

    MainWindowLayout -> addWidget(LogoWidget, 1, 1, 1, 2);
    MainWindowLayout -> addLayout(LeftButtonLayout, 2, 1);
    MainWindowLayout -> addWidget(Chessboard, 2, 2);

    setLayout(MainWindowLayout);

    //setup connect
    connect(ExitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(StartNewGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    connect(Chessboard, SIGNAL(gameEnded(int)), this, SLOT(refreshBoard(int)));
    connect(LoadExistsGameButton, SIGNAL(clicked()), this, SLOT(getSaved()));
    return;
}

mainWidget::~mainWidget()
{
}

void mainWidget::startNewGame()
{
    playerselecter *selecter = new playerselecter();
    int ret = selecter -> exec();
    //qDebug() << ret;
    delete selecter;
    if (ret == -1) return;
    ioInteractor * Port = new ioInteractor(ret);
    Port -> startGame();
    qDebug() << "PORT" ;
    return;
}

void mainWidget::refreshBoard(int opt)
{
    Chessboard -> reset();
    return;
}

void mainWidget::getSaved() {
    QString filename = QFileDialog::getOpenFileName(this, tr("choose a data file"), "", tr("Data(*.dat)"));
    if (filename.isNull()) return;
    qDebug() << filename ;
    return;
}
