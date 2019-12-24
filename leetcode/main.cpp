#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;

int c[maxn];

int n, m;

int check(int mm)
{
    int Count = 1;
    int tmp = 0;
    for (int i = 0; i < n; ++i)
    {
        tmp += c[i];
        if (tmp > mm)
        {
            Count++;
            tmp = 0;
            tmp += c[i];
        }
    }
    return Count;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &c[i]);
    }
    int Max = -1;
    for (int i = 0; i < n; ++i)
        Max = max(Max, c[i]);
    int l = Max - 1, r = 1e9 + 10;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (check(mid) > m)
            l = mid;
        else
            r = mid;
    }
    cout << r << endl;
    return 0;
}