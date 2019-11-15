
#ifndef KDTREE_H
#define KDTREE_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"KDNode.h"

using namespace std;

class KDTree
{
    private:
        /* data */
        KDNode* root; //根结点
        int count; //结点的数量
        int featureId; //第r维特征

    public:
        KDTree(){ root = NULL; count = 0; featureId = 0; }
        ~KDTree();
        bool compare(vector<int> i, vector<int> j);
        int partition(vector<vector<int>>& ts,int low,int high);
        void Qsort(vector<vector<int>>& ts,int low,int high);
        int height(KDNode* root);
        double calculateEucDistance(vector<int> i, vector<int> j);
        vector<int> calculateSplitPoint(vector<vector<int>>& trainingSet, int low, int high);
        void insert(vector<int>& splitpoint);
        KDNode* insertHelp(KDNode* root, vector<int>& splitpoint);
        void updateFeatureId(int n){ featureId = (featureId+1) % n; }
        int getFeatureId(){ return featureId; }

};


#endif


