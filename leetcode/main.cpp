#include <iostream>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <vector>
#include <map>
#include <stdio.h>
#include <time.h>
#include <regex>
#include <string>

using namespace std;

bool isPalindrome(string n)
{
    if (n.size() == 0)
        return false;
    int i, j;
    for (i = 0, j = n.size() - 1; i <= j; i++, j--)
    {
        if (n[i] != n[j])
            return false;
    }
    return true;
}

void check(vector<string> &res, map<pair<string, string>, bool> itemlist, vector<string> &items)
{
    for (int i = 0; i < items.size() - 1; i++)
    {
        for (int j = i + 1; j < items.size(); j++)
        {
            pair<string, string> p1 = pair<string, string>(items[i], items[j]);
            if (itemlist.find(p1) != itemlist.end())
            {
                res.push_back("No");
                return;
            }
        }
    }
    res.push_back("Yes");
}

class student
{
public:
    string id;
    int de;
    int cai;
    student(string s, int d, int c)
    {
        id = s;
        de = d;
        cai = c;
    }
};

bool compare(student s1, student s2)
{
    int t1 = s1.de + s1.cai;
    int t2 = s2.de + s2.cai;
    if (t1 == t2)
    {
        if (s1.de == s2.de)
            return s1.id < s2.id;
        else
            return s1.de > s2.de;
    }
    return t1 > t2;
}

int main()
{
    int n, l, h;
    cin >> n >> l >> h;
    vector<student> vec;
    vector<student> res;
    while (n--)
    {
        string id;
        int d, c;
        cin >> id >> d >> c;
        if (d >= l && c >= l)
            vec.push_back(student(id, d, c));
    }
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].de >= h && vec[i].cai >= h)
        {
            res.push_back(vec[i]);
        }
    }
    sort(res.begin(), res.end(), compare);
    int temp = res.size();
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].de >= h && vec[i].cai < h)
        {
            res.push_back(vec[i]);
        }
    }
    sort(res.begin() + temp, res.end(), compare);
    temp = res.size();
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].de < h && vec[i].cai < h && vec[i].de >= vec[i].cai)
        {
            res.push_back(vec[i]);
        }
    }
    sort(res.begin() + temp, res.end(), compare);
    temp = res.size();
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].de < h && vec[i].de < vec[i].cai)
            res.push_back(vec[i]);
    }
    sort(res.begin() + temp, res.end(), compare);
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i].id << " " << res[i].de << " " << res[i].cai << endl;
    }
}