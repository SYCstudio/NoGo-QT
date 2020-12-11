#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QObject>
#include <QQuickItem>
#include <QWidget>
#include <QPushButton>

class chessGrid : public QPushButton
{
    Q_OBJECT
public:
    int mark;
public:
    explicit chessGrid(QWidget *parent = nullptr);
    int getMark();

signals:
public slots:
    void setMark(int opt = 1);
};

#endif // CHESSGRID_H
