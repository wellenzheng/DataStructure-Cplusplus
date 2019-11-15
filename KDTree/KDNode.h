#ifndef KDNODE_H
#define KDNODE_H

#include <vector>

using namespace std;

class KDNode
{
private:
    double x, y;
    int axis;
    KDNode *lc;
    KDNode *rc;

public:
    KDNode() {}
    KDNode(double x, double y, int axis)
    {
        this->x = x;
        this->y = y;
        this->axis = axis;
        lc = rc = nullptr;
    }
    pair<double, double> getCoordinate()
    {
        return pair<double, double>(x, y);
    }
    void setCoordinate(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    int getAxis() { return axis; }
    void setAxis(int axis) { this->axis = axis; }
    KDNode *left() { return lc; }
    void setLeft(KDNode *l) { lc = l; }
    KDNode *right() { return rc; }
    void setRight(KDNode *r) { rc = r; }
    bool isLeaf() { return lc == nullptr && rc == nullptr; }
    friend ostream &operator<<(ostream &out, KDNode *root)
    {
        out << "(" << root->getCoordinate().first << ", " << root->getCoordinate().second << ")";
        return out;
    }
};

#endif