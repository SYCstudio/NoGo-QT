#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class mainGameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainGameWindow(QWidget *parent = nullptr);
private:
    QWidget *chessBoard;//board placeHolder
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

signals:

};

#endif // MAINGAMEWINDOW_H
