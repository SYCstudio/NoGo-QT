#include "iointeractor.h"

ioInteractor::ioInteractor(int _Player) : QWidget()
{
    Player[0] = _Player / 10;
    Player[1] = _Player % 10;
    if (Player[0] > 0) AI_ID = 1;
    if (Player[1] > 0) AI_ID = 0;
    int show_msg = 1;
    if (Player[0] > 0 && Player[1] > 0) show_msg = 0;
    Game = new mainGameWindow(nullptr, show_msg);
    Game -> setDisable();
    Game -> show();
    connect(Game, SIGNAL(anyGridClicked()), this, SLOT(aiMove()));
    //connect(Game, SLOT(gameEnded(int)), this, SLOT(gameEnded()));
    AI::INIT();
    return;
}

void ioInteractor::startGame()
{
    if (Player[0] == 0 && Player[1] == 0) {
        Game -> rePaintBoard();
        return;
    }
    if (Player[0] != 0 && Player[1] != 0) {
        while (Game -> isGameEnded() == 0) {
            std::pair<int, int> ret = AI::AI(Game -> getBoard());
            Game -> place(ret.first, ret.second);
            //qDebug() << ret.first << ret.second;
            Game -> rePaintBoard();
            //延时
            QEventLoop loop;
            QTimer::singleShot(50, &loop, SLOT(quit()));
            loop.exec();
        }
        return;
    }
    if (Player[0] == 0) {
        Game -> rePaintBoard();
        return;
    }
    std::pair<int, int> ret = AI::AI(Game -> getBoard());
    while (Game -> check(ret.first, ret.second, 0) == 0) ret = AI::AI(Game -> getBoard());
    //qDebug() << ret.first << ret.second;
    Game -> place(ret.first, ret.second, 0);
    Game -> rePaintBoard();
    return;
}

void ioInteractor::aiMove() {
    if ((Game -> getTurncnt() & 1) == AI_ID) return;
    std::pair<int, int> ret = AI::AI(Game -> getBoard());
    while (Game -> check(ret.first, ret.second, 0) == 0) ret = AI::AI(Game -> getBoard());
    //qDebug() << ret.first << ret.second;
    Game -> place(ret.first, ret.second, 0);
    Game -> rePaintBoard();
    return;
}
