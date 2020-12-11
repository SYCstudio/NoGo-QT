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
    explicit chessGrid(QWidget *parent = nullptr);
private:
    int mark;

signals:
private slots:
    void setMark(int opt = 1);
};

#endif // CHESSGRID_H
