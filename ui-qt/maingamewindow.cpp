#include "maingamewindow.h"

mainGameWindow::mainGameWindow(QWidget *parent,int show_msg) : QWidget(parent)
{
    //initialize labels and buttons.
    TimePrompt = new QLabel();
    TimeShow = new QLabel();
    TimePrompt -> setText(tr("Time:"));

    TurnPrompt = new QLabel();
    TurnShow = new QLabel();
    TurnPrompt -> setText(tr("Turn:"));

    SaveButton = new QPushButton();
    SaveButton -> setText(tr("Save"));

    UndoButton = new QPushButton();
    UndoButton -> setText(tr("Undo"));
    UndoButton -> setEnabled(0);

    QuitButton = new QPushButton();
    QuitButton -> setText(tr("Quit"));

    for (int i = 0; i < 81; i++) {
        HistoryButtons[i] = new QPushButton();
        HistoryButtons[i] -> setFixedSize(10,50);
        HistoryButtons[i] -> setEnabled(0);
    }

    ChessBoard = new chessboardBase(nullptr, 50, show_msg);

    //initialize layout
    RightLayout = new QGridLayout();
    RightLayout -> addWidget(TimePrompt, 1, 1);
    RightLayout -> addWidget(TimeShow, 1, 2);
    RightLayout -> addWidget(TurnPrompt, 2, 1);
    RightLayout -> addWidget(TurnShow, 2, 2);
    RightLayout -> addWidget(SaveButton, 3, 1, 1, 2);
    RightLayout -> addWidget(UndoButton, 4, 1, 1, 2);
    RightLayout -> addWidget(QuitButton, 5, 1, 1, 2);

    BottomLayout = new QHBoxLayout();
    BottomLayout -> setSpacing(0);
    for (int i = 0; i < 81; i++) BottomLayout -> addWidget(HistoryButtons[i]);

    MainLayout = new QGridLayout();
    MainLayout -> addWidget(ChessBoard, 1, 1);
    MainLayout -> addLayout(RightLayout, 1, 2);
    MainLayout -> addLayout(BottomLayout, 2, 1, 1, 2);

    setLayout(MainLayout);

    //setup connect
    connect(QuitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ChessBoard, SIGNAL(turncntChanged()), this, SLOT(turncntChanged()));
    connect(ChessBoard, SIGNAL(gameEnded(int)), this, SLOT(gameEnded(int)));
    connect(UndoButton, SIGNAL(clicked()), ChessBoard, SLOT(undo_buf()));
    connect(ChessBoard, SIGNAL(anyGridClicked()), this, SIGNAL(anyGridClicked()));
    connect(SaveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));

    QSignalMapper *historyMapper = new QSignalMapper();
    for (int i = 0; i < 81; i++) connect(HistoryButtons[i], SIGNAL(clicked()), historyMapper, SLOT(map()));
    for (int i = 0; i < 81; i++) historyMapper -> setMapping(HistoryButtons[i], i+1);
    connect(historyMapper, SIGNAL(mapped(int)), ChessBoard, SLOT(repaintBoard(int)));
    connect(historyMapper, SIGNAL(mapped(int)), this, SLOT(changeNowDisplayPointer(int)));
    //*/

    return;
}

void mainGameWindow::setDisable() {
    ChessBoard -> setDisable();
    return;
}

void mainGameWindow::gameEnded(int opt)
{
    ChessBoard -> repaintBoard();
    QString buf(tr("The game is end.\nThe winner is "));
    buf += opt? tr("black") : tr("white");
    QMessageBox::information(this, tr("end."), buf, QMessageBox::Ok);
    close();
}

void mainGameWindow::turncntChanged()
{
    changeNowDisplayPointer(ChessBoard -> getTurncnt());
    for (int i = 0; i < 81; i++) HistoryButtons[i] -> setEnabled(i < ChessBoard -> getTurncnt());
    TurnShow -> setText(QString::number(ChessBoard -> getTurncnt()));
    return;
}

void mainGameWindow::changeNowDisplayPointer(int p)
{
    //qDebug() << "changePointer" << p << ChessBoard -> getTurncnt();
    UndoButton -> setEnabled(p && p == ChessBoard -> getTurncnt());
    return;
}

void mainGameWindow::saveButtonClicked() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Choose filename"), "", tr("Data(*.dat"));
    if (!filename.isNull()) ChessBoard -> SaveData(filename);
    return;
}
