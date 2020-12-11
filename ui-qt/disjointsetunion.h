#ifndef DISJOINTSETUNION_H
#define DISJOINTSETUNION_H

#include <vector>
#include <stack>

class stackData
{
public:
    int x, y, yfa, xsize;
};

class disjointSetUnion
{
public:
    disjointSetUnion(int sz = 100);
    std::vector<int> Dsu, size;

    int getStacktop();
    int merge(int x,int y);
    int getfa(int x);
    void undo(int top = -1);
private:
    std::stack<stackData> stack;
};

#endif // DISJOINTSETUNION_H
