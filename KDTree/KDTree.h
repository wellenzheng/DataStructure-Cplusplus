#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include "KDNode.h"

using namespace std;

class KDTree
{
private:
    KDNode *root;
    int count;
    KDNode *insertHelp(KDNode *root, double x, double y, int axis)
    {
        if (root == nullptr)
            return new KDNode(x, y, axis);
        if (axis == 0 && x < root->getCoordinate().first)
            root->setLeft(insertHelp(root->left(), x, y, axis));
        else
            root->setLeft(insertHelp(root->right(), x, y, axis));
        if (axis == 1 && y < root->getCoordinate().second)
            root->setLeft(insertHelp(root->left(), x, y, axis));
        else
            root->setRight(insertHelp(root->right(), x, y, axis));
    }
    void printHelp(KDNode *root)
    {
        if (root == nullptr)
            return;
        cout << root << endl;
        printHelp(root->left());
        printHelp(root->right());
    }

public:
    KDTree()
    {
        root = new KDNode();
        count = 0;
    };
    void insert(double x, double y, int axis)
    {
        root = insertHelp(root, x, y, axis);
        count++;
    }
};

#endif