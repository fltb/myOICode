/*
12 4
1
3
2
4
2
1
2
3
1
1
3
4

1 3 2 4 2 1 2 3 1  1  3  4
1 2 3 4 5 6 7 8 9 10 11 12


*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 2, MAXM = 20, INF = 0x7fffffff;
// all begins at **1**
int teams[MAXM+1], //each team's num
    sum[MAXM+1][MAXN], //sum[team][cur] is the singers of the teams on the cur(included)
    f[(1<<MAXM) + 10],
    n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        int tmp;
        scanf("%d", &tmp);
        ++teams[tmp];
        //each teams add cur
        for (int j = 1; j <= m; ++j)
        {
            sum[j][i] = sum[j][i-1];
        }
        ++sum[tmp][i];
    }
    for(int i = 1; i <= (1<<m); ++i)
    {
        f[i] = INF;
    }
    for (int i = 1; i < (1<<m); ++i)
    {
        int len = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (i & (1 << (j-1) ) )
            {
                len += teams[j];
            }
        }

        for(int j = 1; j <= m; ++j)
        {
            if (i & (1 << (j-1) ) )
            {
                f[i] = min(f[i],
                           f[(i ^ (1 << (j-1)))] + teams[j] - sum[j][len] + sum[j][len - teams[j] ] );
            }
        }
    }

    cout<<f[(1<<m) - 1];
}
