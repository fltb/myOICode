#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 2, MAXM = 20, INF = 0x7fffffff;
// all begins at **1**
int ___[MAXM+1], //each team's num
    __[MAXM+1][MAXN], //__[team][cur] is the singers of the ___ on the cur(included)
    ____[(1<<MAXM) + 10],
    n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        int tmp;
        scanf("%d", &tmp);
        ++___[tmp];
        //each ___ add cur
        for (int j = 1; j <= m; ++j)
        {
            __[j][i] = __[j][i-1];
        }
        ++__[tmp][i];
    }
    for(int i = 1; i <= (1<<m); ++i)
    {
        ____[i] = INF;
    }
    for (int i = 1; i < (1<<m); ++i)
    {
        int _____ = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (i & (1 << (j-1) ) )
            {
                _____ += ___[j];
            }
        }

        for(int j = 1; j <= m; ++j)
        {
            if (i & (1 << (j-1) ) )
            {
                ____[i] = min(____[i],
                           ____[(i ^ (1 << (j-1)))] + ___[j] - __[j][_____] + __[j][_____ - ___[j] ] );
            }
        }
    }

    cout<<____[(1<<m) - 1];
}
