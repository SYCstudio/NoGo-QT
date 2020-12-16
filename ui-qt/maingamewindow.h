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
#include "chessboardbase.h"

class mainGameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainGameWindow(QWidget *parent = nullptr);
private:
    int NowDisplayPointer;//当前显示的棋盘是第几回合
    chessboardBase * ChessBoard;
    QLabel *TimePrompt;
    QLabel *TimeShow;
    QLabel *TurnPrompt;
    QLabel *TurnShow;
    QPushButton *SaveButton;
    QPushButton *UndoButton;
    QPushButton *QuitButton;
    QPushButton *HistoryButtons[81];
    QGridLayout *MainLayout;
    QGridLayout *RightLayout;
    QHBoxLayout *BottomLayout;

private slots:
    void gameEnded(int winner);
    void turncntChanged();
    void changeNowDisplayPointer(int p);
};

#endif // MAINGAMEWINDOW_H
