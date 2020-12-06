#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define id(x, y) ((x - 1) * n + y)
#define inBd(x, y) (x >= 1 && y >= 1 && x <= n && y <= n)
#define outBd(x, y) (!inBd(x, y))

const int maxN = 650;
const int Fx[] = {-1, 0, 1, 0};
const int Fy[] = {0, 1, 0, -1};

int n;
int Bd[maxN][maxN];
int Ufs[maxN * maxN], Air[maxN * maxN], Mark[maxN * maxN];
queue<pair<int, int> > Qu,Bq[2];

void outp();
int find(int id);
bool check(int x, int y, int col);
void maintain(int x, int y, int col);

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) Ufs[id(i, j)]=id(i, j);
    memset(Bd, -1, sizeof(Bd));
    for (int i = 1; i <= n; i++) {
        char input[maxN];
        cin >> (input + 1);
        for (int j = 1; j <= n; j++) {
            if (input[j] == 'X') maintain(i, j, 0);
            else if (input[j]=='O') maintain(i, j, 1);
            else Qu.push(make_pair(i, j));
            //outp();
        }
    }

    int col = 0;
    while (Qu.size() + Bq[col].size() > 0) {
        bool flag = 0;
        while (flag == 0 && Qu.size() > 0) {
            int x=Qu.front().first, y=Qu.front().second;
            Qu.pop();
            if (check(x, y, col)) {
                maintain(x, y, col);
                flag = 1;
                cout << x << " " << y << endl;
            }
            else Bq[col ^ 1].push(make_pair(x, y));
        }
        while (flag == 0 && Bq[col].size() > 0) {
            int x=Bq[col].front().first, y=Bq[col].front().second;
            Bq[col].pop();
            if (check(x, y, col)) {
                maintain(x, y, col);
                flag = 1;
                cout << x << " " << y <<endl;
            }
        }
        if (flag == 0) break;
        //outp();
        col ^= 1;
    }
    puts("-1 -1");
    return 0;
}

void outp() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cout << i << " " << j << ":" << Air[find(id(i, j))] << endl;
    return;
}

int find(int id) {
    if (Ufs[id] != id) Ufs[id] = find(Ufs[id]);
    return Ufs[id];
}

bool check(int x, int y, int col) {
    if (Bd[x][y] != -1) return 0;

    int air = 0; int flag = 1;
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (Bd[xx][yy] == -1) ++air;
        else if (Bd[xx][yy] == col) {
            int anc = find(id(xx, yy));
            air += (Mark[anc] ^ 1) * Air[anc] - 1;
            Mark[anc] = 1;
        }
        else if (Bd[xx][yy] == (col ^ 1)) {
            --Air[find(id(xx, yy))];
            if (Air[find(id(xx, yy))] == 0) flag = 0;
        }
    }

    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (Bd[xx][yy] == (col ^ 1)) ++Air[find(id(xx, yy))];
        else if (Bd[xx][yy] == col) Mark[find(id(xx, yy))] = 0;
    }

    return air * flag > 0;
}

void maintain(int x, int y, int col) {
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy) || Bd[xx][yy] == -1) continue;
        --Air[find(id(xx, yy))];
    }
    Bd[x][y] = col;
    int air = 0;
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy) || Bd[xx][yy] == (col ^ 1)) continue;
        if (Bd[xx][yy] == -1) {
            ++air; continue;
        }
        int anc = find(id(xx, yy));
        if (anc == id(x, y)) continue;
        air += Air[anc];
        Ufs[anc] = id(x, y);
    }
    Air[id(x, y)] = air;
    return;
}