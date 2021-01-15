#include "maingamewindow.h"

mainGameWindow::mainGameWindow(QWidget *parent,int show_msg) : QWidget(parent)
{
    //initialize labels and buttons.
    //TimePrompt = new QLabel();
    //TimeShow = new QLabel();
    //TimePrompt -> setText(tr("Time:"));
    setWindowTitle(tr("Have fun"));

    TurnPrompt = new QLabel();
    TurnShow = new QLabel();
    TurnPrompt -> setText(tr("Turn:"));

    is_tips = 0;
    TipsButton = new QPushButton();
    TipsButton -> setText(tr("Tips(Off)"));

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
    //RightLayout -> addWidget(TimePrompt, 1, 1);
    //RightLayout -> addWidget(TimeShow, 1, 2);
    RightLayout -> addWidget(TurnPrompt, 1, 1);
    RightLayout -> addWidget(TurnShow, 1, 2);
    RightLayout -> addWidget(TipsButton, 2, 1, 1, 2);
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
    QSignalMapper *historyMapper = new QSignalMapper();
    for (int i = 0; i < 81; i++) connect(HistoryButtons[i], SIGNAL(clicked()), historyMapper, SLOT(map()));
    for (int i = 0; i < 81; i++) historyMapper -> setMapping(HistoryButtons[i], i+1);
    connect(historyMapper, SIGNAL(mapped(int)), ChessBoard, SLOT(repaintBoard(int)));
    connect(historyMapper, SIGNAL(mapped(int)), this, SLOT(changeNowDisplayPointer(int)));

    connect(QuitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ChessBoard, SIGNAL(turncntChanged()), this, SLOT(turncntChanged()));
    connect(ChessBoard, SIGNAL(gameEnded(int)), this, SLOT(gameEnded(int)));
    connect(UndoButton, SIGNAL(clicked()), this, SLOT(undo_buf()));
    connect(ChessBoard, SIGNAL(anyGridClicked()), this, SIGNAL(anyGridClicked()));
    connect(SaveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
    connect(TipsButton, SIGNAL(clicked()), this, SLOT(tipschanged()));
    //*/

    return;
}

void mainGameWindow::gameEnded(int opt)
{
    ChessBoard -> repaintBoard();
    QString buf(tr("The game is end.\nThe winner is "));
    buf += opt? tr("black") : tr("white");
    QMessageBox::information(this, tr("Game End"), buf, QMessageBox::Ok);
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
    UndoButton -> setEnabled(p && p == ChessBoard -> getTurncnt() && is_ai == 0);
    return;
}

void mainGameWindow::saveButtonClicked() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Choose filename"), "", tr("Data(*.dat)"));
    if (!filename.isNull()) {
        emit saveSignal(filename);
        ChessBoard -> SaveData(filename);
    }
    return;
}

void mainGameWindow::setPlayerDetail(int p1, int p2)
{
    P1 = p1; P2 = p2;
    is_ai = (p1 > 0 && p2 > 0);
    if (is_ai) {
        UndoButton -> setEnabled(0);
        SaveButton -> setEnabled(0);
        QuitButton -> setEnabled(0);
        TipsButton -> setEnabled(0);
    }
    return;
}

void mainGameWindow::undo_buf()
{
    //qDebug() << P1 << P2;
    if (P1 == 0 && P2 == 0) ChessBoard -> undo_buf();
    else ChessBoard -> undo_buf(), ChessBoard -> undo_buf();
    return;
}

void mainGameWindow::tipschanged()
{
    is_tips ^= 1;
    //qDebug() << "main:" << is_tips;
    if (is_tips) TipsButton -> setText(tr("Tips(On)"));
    else TipsButton -> setText(tr("Tips(Off)"));
    ChessBoard -> changeshowTipsFlag();
    return;
}
