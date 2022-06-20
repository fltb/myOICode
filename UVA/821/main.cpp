#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <iostream>
using std::cin;
using std::cout;
template <typename T>
inline T max(T a, T b)
{
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b)
{
    return a < b ? a : b;
}
const int MAXN = 100 + 2, INF = 0x3f3f3f3f;
int floyd[MAXN][MAXN];
int main()
{
    std::ios::sync_with_stdio(false);
    int t = 1;
    while (true)
    {
        for (int i = 1; i < MAXN; i++)
        {
            for (int j = 1; j < MAXN; j++)
            {
                floyd[i][j] = INF;
            }
        }
        int n = 0;
        while (true)
        {
            int u, v;
            cin >> u >> v;
            if (u == 0 && v == 0)
            {
                break;
            }
            n++;
            floyd[u][v] = 1;
        }
        if (n == 0)
        {
            break;
        }

        for (int k = 1; k < MAXN; k++)
        {
            for (int i = 1; i < MAXN; i++)
            {
                for (int j = 1; j < MAXN; j++)
                {
                    if (i == j || i == k || j == k)
                    {
                        continue;
                    }
                    if (min(floyd[i][k], floyd[k][j]) < INF)
                    {
                        floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
                    }
                }
            }
        }
        long long tot = 0, ctt = 0;
        for (int i = 1; i < MAXN; i++)
        {
            for (int j = 1; j < MAXN; j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (floyd[i][j] < INF)
                {
                    tot += floyd[i][j];
                    ctt += 1;
                }
            }
        }
        cout << "Case " << t++ << ": average length between pages = " << std::fixed << std::setprecision(3) << (double)tot / ctt << " clicks\n";
    }
    return 0;
}