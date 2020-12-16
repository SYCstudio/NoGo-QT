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
    chessboardBase * ChessBoard;
    QLabel *TimePrompt;
    QLabel *TimeShow;
    QLabel *TurnPrompt;
    QLabel *TurnShow;
    QPushButton *SaveButton;
    QPushButton *QuitButton;
    QPushButton *HistoryButtons[81];
    QGridLayout *MainLayout;
    QGridLayout *RightLayout;
    QHBoxLayout *BottomLayout;

private slots:
    void gameEnded(int winner);
    void turncntChanged();
};

#endif // MAINGAMEWINDOW_H
