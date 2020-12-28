#include "iointeractor.h"

ioInteractor::ioInteractor(int _Player, mainGameWindow *buf) : QWidget()
{
    Player[0] = _Player / 10;
    Player[1] = _Player % 10;
    if (Player[0] > 0) AI_ID = 1;
    if (Player[1] > 0) AI_ID = 0;
    int show_msg = 1;
    if (Player[0] > 0 && Player[1] > 0) show_msg = 0;

    if (buf == nullptr) Game = new mainGameWindow(nullptr, show_msg);
    else Game = buf;

    //qDebug() << "Player " << Player[0] << Player[1];
    for (int id = 0; id < 2; id++) AI[id ^ 1] = new aimodule(Player[id]);

    Game -> show();
    Game -> rePaintBoard();

    connect(Game, SIGNAL(anyGridClicked()), this, SLOT(aiMove()));
    connect(Game, SIGNAL(saveSignal(QString)), this, SLOT(write(QString)));
    //connect(Game, SLOT(gameEnded(int)), this, SLOT(gameEnded()));

    return;
}

void ioInteractor::startGame()
{
    if (Player[0] == 0 && Player[1] == 0) {
        Game -> rePaintBoard();
        return;
    }
    if (Player[0] != 0 && Player[1] != 0) {
        int opt = 0;//当前执子者
        while (Game -> isGameEnded() == 0) {
            std::pair<int, int> ret = AI[opt] -> getPos(Game -> getBoard());
            Game -> place(ret.first, ret.second);
            //qDebug() << ret.first << ret.second;
            Game -> rePaintBoard();
            //延时
            QEventLoop loop;
            QTimer::singleShot(50, &loop, SLOT(quit()));
            loop.exec();
            opt ^= 1;
        }
        return;
    }
    if (Player[0] == 0) {
        Game -> rePaintBoard();
        return;
    }
    std::pair<int, int> ret = AI[0] -> getPos(Game -> getBoard());
    //qDebug() << ret.first << ret.second;
    Game -> place(ret.first, ret.second, 0);
    Game -> rePaintBoard();
    return;
}

void ioInteractor::write(QString filename)
{
    //qDebug() << "write:" << filename;
    QFile writef(filename);
    if (!writef.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warning!"), tr("Can't write data to file."), QMessageBox::Ok);
        return;
    }

    QTextStream out(&writef);

    out << Player[0] << " " << Player[1] << "\n";

    writef.close();
    return;
}

void ioInteractor::aiMove() {
    if ((Game -> getTurncnt() & 1) == AI_ID) return;
    if (Player[0] == 0 && Player[1] == 0) return;
    std::pair<int, int> ret = AI[AI_ID] -> getPos(Game -> getBoard());
    //qDebug() << "ret:" << ret.first << ret.second;
    Game -> place(ret.first, ret.second, 0);
    Game -> rePaintBoard();
    return;
}
