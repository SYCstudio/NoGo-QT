#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include "chessboardbase.h"

class mainGameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainGameWindow(QWidget *parent = nullptr);
private:
    chessboardBase * chessBoard;
    QLabel *timePrompt;
    QLabel *timeShow;
    QLabel *turnPrompt;
    QLabel *turnShow;
    QPushButton *saveButton;
    QPushButton *quitButton;
    QPushButton *historyButtons[81];
    QGridLayout *mainLayout;
    QGridLayout *rightLayout;
    QHBoxLayout *bottomLayout;

private slots:
    void turnShowRefresh();
    void gameEnd(int opt);

};

#endif // MAINGAMEWINDOW_H
