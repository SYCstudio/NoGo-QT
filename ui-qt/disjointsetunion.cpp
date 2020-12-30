#include "disjointsetunion.h"

disjointSetUnion::disjointSetUnion(int sz)
{
    Dsu.resize(sz+10);
    size.resize(sz+10);
    for (int i = 1; i < sz+10; i++) Dsu[i] = i, size[i] = 1;
    return;
}

int disjointSetUnion::getStacktop()
{
    return stack.size();
}
int disjointSetUnion::merge(int x, int y)
{
    return _merge(x, y);
}
int disjointSetUnion::_merge(int x,int y)
{
    x = _getfa(x);
    y = _getfa(y);
    if (size[x] < size[y]) std::swap(x, y);

    stack.push((stackData){x, y, Dsu[y], size[x]});

    Dsu[y] = x; size[x] += size[y];
    return x;
}
int disjointSetUnion::getfa(int x){
    return _getfa(x);
}
int disjointSetUnion::_getfa(int x)
{
    while (Dsu[x] != x) x= Dsu[x];
    return x;
}
void disjointSetUnion::undo(int top)
{
    if (top == -1) {
        if (stack.size() == 0) return;
        top = stack.size()-1;
    }
    while ((int)stack.size() != top) {
        stackData buf = stack.top(); stack.pop();
        Dsu[buf.y] = buf.x;
        size[buf.x] = buf.xsize;
    }
    return;
}
