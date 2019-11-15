
#ifndef KDNode_H
#define KDNode_H

#include<iostream>
#include<vector>
#include<string>


using namespace std;

class KDNode
{
    private:
        /* data */
        int FeatureId; //结点所选取的特征，即切分轴，取值范围为0~n-1，公式为r=(r+1) mod n
        vector<int> SplitPoint; //分割点，是一个n维向量
        KDNode* lc; //左子树指针
        KDNode* rc; //右子树指针

    public:
        KDNode(){ lc = NULL; rc = NULL;}
        KDNode(int featureid, vector<int> splitpoint){ FeatureId = featureid; SplitPoint = splitpoint; }
        ~KDNode(){}
        inline pair<int,vector<int>> getElement(){ return pair<int,vector<int>>(FeatureId,SplitPoint); };
        inline int getFeatureId(){ return FeatureId; }
        inline vector<int> getSplitPoint(){ return SplitPoint; }
        void setFeatureId(int featureid){ FeatureId  =  featureid; }
        void setSplitPoint(vector<int> splitpoint){ SplitPoint = splitpoint; }
        void setElement(int featureid,vector<int>& splitpoint){ FeatureId  =  featureid; SplitPoint  =  splitpoint;}
        inline KDNode* left() const{ return lc; }
        inline KDNode* right() const{ return rc; }
        void setLeft(KDNode* node){ lc  =  node; }
        void setRight(KDNode* node){ rc  =  node; }
        bool isLeaf(){ return (lc == NULL && rc == NULL); }
};

#endif
