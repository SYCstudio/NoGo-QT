#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QSignalMapper>
#include <QFileDialog>
#include "chessboardbase.h"

class mainGameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainGameWindow(QWidget *parent = nullptr,int show_msg = 1);
    void setDisable(){ChessBoard -> setDisable();}
    int getTurncnt(){return ChessBoard -> getTurncnt();}
    int isGameEnded(){return ChessBoard -> isGameEnded();}
    void rePaintBoard(){ChessBoard -> repaintBoard();}
    std::vector<std::pair<int, int> > getBoard(){return ChessBoard -> getBoard();}
    int check(int x, int y, int show_msg = -1){return ChessBoard -> check(x, y, show_msg);}
    void place(int x, int y,int show_msg = -1){ChessBoard -> place(x, y, show_msg);}
    void setPlayerDetail(int p1, int p2);

private:
    int NowDisplayPointer;//当前显示的棋盘是第几回合
    bool is_ai;
    chessboardBase * ChessBoard;
    //QLabel *TimePrompt;
    //QLabel *TimeShow;
    QLabel *TurnPrompt;
    QLabel *TurnShow;
    QPushButton *SaveButton;
    QPushButton *UndoButton;
    QPushButton *QuitButton;
    QPushButton *HistoryButtons[81];
    QGridLayout *MainLayout;
    QGridLayout *RightLayout;
    QHBoxLayout *BottomLayout;
signals:
    void anyGridClicked();
    void saveSignal(QString filename);
private slots:
    void gameEnded(int winner);
    void turncntChanged();
    void changeNowDisplayPointer(int p);
    void saveButtonClicked();
};

#endif // MAINGAMEWINDOW_H
