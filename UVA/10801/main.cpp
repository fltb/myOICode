#include <algorithm>
#include <cctype>
#include <cstdio>
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
const int INF = 0x7fffffff,
          MAXN = 100 + 2,
          MAXK = 5 + 1,
          CHANGE = 60;

long long flooring[MAXN], lift[MAXK];
bool hasLift[MAXN][MAXK], vis[MAXN];
int main()
{
    std::ios::sync_with_stdio(false);
    int n, m;
    auto abs = [](long long val)
    {
        if (val < 0)
        {
            return 0ll - val;
        }
        else
        {
            return val;
        }
    };
    auto clean2n = [](){
        while (cin.peek() != '\n') {
            cin.get();
        }
        cin.get();
    };
    while (cin >> n >> m)
    {
        // init
        for (int i = 0; i < MAXN; i++)
        {
            flooring[i] = INF;
            vis[i] = false;
            for (int k = 0; k < MAXK; k++)
            {
                hasLift[i][k] = false;
            }
        }
        for (int k = 0; k < MAXK; k++)
        {
            lift[k] = 0;
        }

        for (int i = 0; i < n; i++)
        {
            cin >> lift[i];
        }
        clean2n();
        for (int i = 0; i < n; i++)
        {
            while (cin.peek() != '\n')
            {
                int flr;
                cin >> flr;
                hasLift[flr][i] = true;
            }
            clean2n();
        }

        // Dijkstra
        flooring[0] = -CHANGE;  // 减去最初换乘的
        for (int _ = 1; _ < MAXN; _++)
        {
            // 取出当前最小点
            int cur = MAXN, mn = INF;
            for (int i = 0; i < MAXN; i++)
            {
                if (!vis[i] && flooring[i] < mn)
                {
                    mn = flooring[i];
                    cur = i;
                }
            }
            if (cur == MAXN)
            {
                break;
            }
            vis[cur] = true;
            for (int i = 0; i < MAXN; i++)
            {
                if (i == cur)
                {
                    continue;
                }
                for (int k = 0; k < n; k++)
                {
                    // 尝试换乘
                    if (hasLift[cur][k] && hasLift[i][k])
                    {
                        flooring[i] = min(flooring[i], flooring[cur] + lift[k] * abs(i - cur) + CHANGE);
                    }
                }
            }
        }

        if (flooring[m] < INF)
        {
            cout << max(0ll, flooring[m]) << '\n';
        }
        else
        {
            cout << "IMPOSSIBLE\n";
        }
    }
    return 0;
}