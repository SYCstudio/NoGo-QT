#ifndef AIMODULE_H
#define AIMODULE_H

#include <QWidget>
#include <random>
#include <ctime>
#include <vector>
#include "nogochessboard.h"

using std::vector;
using std::pair;
using std::make_pair;

class aimodule : public QWidget
{
    Q_OBJECT
public:
    int Level;
    explicit aimodule(int level, QWidget *parent = nullptr);
    pair<int, int> getPos(vector<pair<int, int> > Bd);
};

namespace airandom {
    pair<int, int> getPos(vector<pair<int, int> > Bd);
};

#endif // AIMODULE_H
