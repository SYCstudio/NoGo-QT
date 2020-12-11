#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QApplication>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    QPushButton *startNewGameButton;
    QPushButton *loadExistsGameButton;
    QPushButton *exitButton;
    QGridLayout *mainWindowLayout;
    QVBoxLayout *leftButtonLayout;
    QWidget *logoWidget;//logo placeHolder
    QWidget *rightWidget;//right placeHolder
};
#endif // MAINWIDGET_H
