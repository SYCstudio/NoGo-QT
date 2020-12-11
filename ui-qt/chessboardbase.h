#ifndef CHESSBOARDBASE_H
#define CHESSBOARDBASE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class chessboardBase : public QWidget
{
    Q_OBJECT
public:
    explicit chessboardBase(QWidget *parent = nullptr, int size = 50);

signals:
private:
    int boardStatus[9][9];
    QPushButton *boardButton[9][9];
    QGridLayout *boardLayout;
};

#endif // CHESSBOARDBASE_H
