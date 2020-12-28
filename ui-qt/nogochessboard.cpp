#include "nogochessboard.h"

nogochessboard::nogochessboard(QWidget *parent,int show_msg) : QWidget(parent)
{
    SHOW_MSG = show_msg;
    //qDebug() << show_msg;
    memset(Air, 0, sizeof(Air));
    memset(PlaceX, 0, sizeof(PlaceX));
    memset(PlaceY, 0, sizeof(PlaceY));
    memset(BoardStatus, -1, sizeof(BoardStatus));
    memset(TopPositionRecord, 0, sizeof(TopPositionRecord));
    Turncnt = 0;
    dsu = new disjointSetUnion(81);
    is_game_end = 0;
    return;
}

void nogochessboard::reset() {
    memset(Air, 0, sizeof(Air));
    memset(PlaceX, 0, sizeof(PlaceX));
    memset(PlaceY, 0, sizeof(PlaceY));
    memset(BoardStatus, -1, sizeof(BoardStatus));
    memset(TopPositionRecord, 0, sizeof(TopPositionRecord));
    Turncnt = 0;
    delete dsu;
    dsu = new disjointSetUnion(81);
    is_game_end = 0;
    return;
}

int nogochessboard::check(int x, int y, int show_msg) {
    if (show_msg == -1) show_msg = SHOW_MSG;
    //边界判断
    if (outBd(x, y)) {
        if (show_msg) QMessageBox::warning(this, tr("Warning!"), tr("Invalid position!"), QMessageBox::Ok);
        return 0;
    }
    if (BoardStatus[id(x, y)] != -1) {
        if (show_msg) QMessageBox::warning(this, tr("Warning!"), tr("This position has been filled."), QMessageBox::Ok);
        return 0;
    }
    //先手不能先放在中间位置
    if (Turncnt == 0 && x == 4 && y == 4) {
        if (show_msg) QMessageBox::warning(this, tr("Warning!"), tr("You cannot select the middle position at the first step."), QMessageBox::Ok);
        return 0;
    }

    //检查气
    int air = 0, flag = 1, col = (Turncnt + 1) & 1;
    static int Mark[81];
    memset(Mark, 0, sizeof(Mark));

    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (BoardStatus[id(xx, yy)] == -1) ++air;
        else if (BoardStatus[id(xx, yy)] == col) {
            int anc = dsu -> getfa(id(xx, yy));
            air += (Mark[anc] ^ 1) * Air[anc] - 1;
            Mark[anc] = 1;
        }
        else if (BoardStatus[id(xx, yy)] == (col ^ 1)) {
            --Air[dsu -> getfa(id(xx, yy))];
            if (Air[dsu -> getfa(id(xx, yy))] == 0) flag = 0;
        }
    }
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (BoardStatus[id(xx, yy)] == (col ^ 1)) ++Air[dsu -> getfa(id(xx, yy))];
        else if (BoardStatus[id(xx, yy)] == col) Mark[dsu -> getfa(id(xx, yy))] = 0;
    }
    //qDebug() << air << flag;
    if (air * flag == 0) return -1;
    return 1;
}

int nogochessboard::checkopp(int x, int y) {
    //边界判断
    if (outBd(x, y)) return 0;
    if (BoardStatus[id(x, y)] != -1) return 0;
    //先手不能先放在中间位置
    if (Turncnt == 0 && x == 4 && y == 4) return 0;

    //检查气
    int air = 0, flag = 1, col = (Turncnt) & 1;
    static int Mark[81];
    memset(Mark, 0, sizeof(Mark));

    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (BoardStatus[id(xx, yy)] == -1) ++air;
        else if (BoardStatus[id(xx, yy)] == col) {
            int anc = dsu -> getfa(id(xx, yy));
            air += (Mark[anc] ^ 1) * Air[anc] - 1;
            Mark[anc] = 1;
        }
        else if (BoardStatus[id(xx, yy)] == (col ^ 1)) {
            --Air[dsu -> getfa(id(xx, yy))];
            if (Air[dsu -> getfa(id(xx, yy))] == 0) flag = 0;
        }
    }
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (BoardStatus[id(xx, yy)] == (col ^ 1)) ++Air[dsu -> getfa(id(xx, yy))];
        else if (BoardStatus[id(xx, yy)] == col) Mark[dsu -> getfa(id(xx, yy))] = 0;
    }
    //qDebug() << air << flag;
    if (air * flag == 0) return -1;
    return 1;
}

void nogochessboard::place(int x, int y, int show_msg) {
    if (show_msg == -1) show_msg = SHOW_MSG;
    int check_ret = check(x, y, show_msg);
    if (check_ret == 0) return;

    //回合数增加
    turncntPlus();
    int col = Turncnt & 1;

    //棋盘填充
    BoardStatus[id(x, y)] = col;
    PlaceX[Turncnt] = x;
    PlaceY[Turncnt] = y;

    //更新气
    TopPositionRecord[Turncnt] = dsu -> getStacktop();//并查集回溯准备
    for (int f = 0; f < 4; f++) {//原始信息记录
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        AirRec[Turncnt][f] = Air[dsu -> getfa(id(xx, yy))];
        AncRec[Turncnt][f] = dsu -> getfa(id(xx, yy));
    }

    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy) || BoardStatus[id(xx,yy)] == -1) continue;
        --Air[dsu -> getfa(id(xx, yy))];
    }
    int air = 0, finalanc = id(x, y);
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy) || BoardStatus[id(xx, yy)] == (col ^ 1)) continue;
        if (BoardStatus[id(xx, yy)] == -1) {
            ++air; continue;
        }
        int anc = dsu -> getfa(id(xx, yy));
        if (anc == finalanc) continue;
        air += Air[anc];
        finalanc = dsu -> merge(anc,finalanc);
    }
    Air[finalanc] = air;

    if (check_ret == -1) {
        emit gameEnded(col ^ 1);
        is_game_end = 1;
    }
    return;
}

void nogochessboard::undo() {
    //qDebug() << "UNDO!" << Turncnt;
    if (Turncnt == 0) return;
    int x = PlaceX[Turncnt], y = PlaceY[Turncnt];
    dsu -> undo(TopPositionRecord[Turncnt]);
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        Air[AncRec[Turncnt][f]] = AirRec[Turncnt][f];
    }
    BoardStatus[id(x, y)] = -1;

    turncntMinus();
    return;
}

std::vector<std::pair<int, int> > nogochessboard::getBoard(int show_turn) {
    if (show_turn == -1) show_turn = Turncnt;
    //qDebug() << "show_turn" << show_turn;
    std::vector<std::pair<int, int> > R;
    for (int i = 1; i <= getTurncnt(); i++) R.push_back(std::make_pair(PlaceX[i], PlaceY[i]));
    return R;
}

void nogochessboard::SaveData(QString filename) {
    QFile writef(filename);
    if (!writef.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warning!"), tr("Can't write data to file."), QMessageBox::Ok);
        return;
    }
    QByteArray array=writef.readAll();
    //qDebug () << array;

    QTextStream out(&writef);

    out << getTurncnt() << "\n";
    for (int i = 1 ; i <= getTurncnt(); i++) out << PlaceX[i] << " " << PlaceY[i] << "\n";
    writef.close();
    return;
}

void nogochessboard::turncntPlus() {
    ++Turncnt;
    emit turncntChanged();
    return;
}

void nogochessboard::turncntMinus() {
    --Turncnt;
    emit turncntChanged();
    return;
}

int nogochessboard::checkPositionColor(int x, int y, int col) {
    if (outBd(x, y)) return 0;
    return BoardStatus[id(x, y)] == col;
}
