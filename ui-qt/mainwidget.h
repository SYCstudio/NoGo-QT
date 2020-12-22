#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QTranslator>
#include "maingamewindow.h"
#include "chessboardbase.h"
#include "playerselecter.h"
#include "iointeractor.h"
#include "languageselector.h"

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    QPushButton *StartNewGameButton;
    QPushButton *LoadExistsGameButton;
    QPushButton *ExitButton;
    QPushButton *LanguageButton;
    QGridLayout *MainWindowLayout;
    QVBoxLayout *LeftButtonLayout;
    QWidget *LogoWidget;//logo placeHolder
    chessboardBase *Chessboard;
    QTranslator * language;

    void setLabel();

private slots:
    void startNewGame();
    void refreshBoard(int opt);
    void getSaved();
    void selectLanguage();
};
#endif // MAINWIDGET_H
