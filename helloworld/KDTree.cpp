#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<math.h>
#include"KDNode.h"
#include"KDTree.h"

// vector<int> getFeatureMid(vector<vector<int>>& ts, int low, int high)
// {
//     int mid=(low+high)/2;
// 	while(1)
// 	{
// 		int pos=partition(ts,low,high);
//         //当pos==mid时，停止排序
// 		if(pos==mid)
// 			break;
// 		else if(pos>mid)
// 			high=pos-1;
// 		else low=pos+1;
// 	}
// 	return ts[mid];
// }

bool KDTree::compare(vector<int> i, vector<int> j){return i.at(featureId) < j.at(featureId);}

int KDTree::partition(vector<vector<int>>& ts,int low,int high)
{
	int i,num=low;
	for(i=low+1;i<=high;i++)
	{
		if(compare(ts[i],ts[low]))
		{
			swap(ts.at(i),ts.at(num+1));
			num++;
		}
	}
	swap(ts.at(low),ts.at(num));
	return num;
}

void KDTree::Qsort(vector<vector<int>>& ts,int low,int high)
{
	if(low < high)
	{
		int pivot=partition(ts,low,high);
		Qsort(ts,low,pivot-1);
		Qsort(ts,pivot+1,high);
	}
}

int KDTree::height(KDNode* root)
{
	if(root == NULL)
		return 0;
	return 1+max(height(root->left()),height(root->right()));
}

double KDTree::calculateEucDistance(vector<int> i, vector<int> j)
{
	int dis=0;
	for (int n = 0; n < i.size(); n++)
	{
		dis+=pow((i.at(n)-j.at(n)),2);
	}
	return sqrt(dis);
}

void KDTree::insert(vector<int>& splitpoint)
{
	root = insertHelp(root, splitpoint);
	// updateFeatureId(2);
	count++;
}

vector<int> KDTree::calculateSplitPoint(vector<vector<int>>& ts, int low, int high)
{
	int mid=(low+high)/2;
	while(1)
	{
		int pos=partition(ts,low,high);
        //当pos==mid时，停止排序
		if(pos==mid)
			break;
		else if(pos>mid)
			high=pos-1;
		else low=pos+1;
	}
	return ts[mid];
}

KDNode* KDTree::insertHelp(KDNode* root, vector<int>& splitpoint)
{
    if(root == NULL)
        return new KDNode(featureId, splitpoint);  
	if(splitpoint[featureId] < (root->getSplitPoint())[featureId])
		root->setLeft(insertHelp(root->left(),splitpoint));
	else
		root->setRight(insertHelp(root->right(),splitpoint));
	return root;
}
