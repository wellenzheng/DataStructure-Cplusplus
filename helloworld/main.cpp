#include<iostream>
#include"KDNode.h"
#include"KDTree.h"

using namespace std;

// bool compare(vector<int> i, vector<int> j){ return i.at(0) < j.at(0); }



// vector<int> getFeatureMid(vector<vector<int>>& trainingSet)
// {
// 	sort(trainingSet.begin(),trainingSet.end(),compare);
// 	return trainingSet.at(trainingSet.size()/2-1);
// }

vector<vector<int>> TrainingSet = 
{
    {1,2},
    {3,4},
    {6,4},
    {8,2},
    {4,5},
    {12,6},
    {13,10},
    {9,9},
    {3,6},
    {1,7}
};


void buildKDTree(KDTree* kdtree, vector<vector<int>>& ts, int low, int high)
{
	vector<int> splitpoint = kdtree->calculateSplitPoint(ts,low,high);
	kdtree->insert(splitpoint);
	int mid = (low+high)/2;
	kdtree->updateFeatureId(2);
	buildKDTree(kdtree,ts,low,mid);
	buildKDTree(kdtree,ts,mid+1,high);
}

int main()
{
	KDTree* kdtree = new KDTree();
	buildKDTree(kdtree,TrainingSet,0,9);
}