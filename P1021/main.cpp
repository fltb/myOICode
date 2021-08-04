#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
const int INF = 0x7fffffff;
const int MAXN = 15+1;

int a[MAXN], fin[MAXN], n = 0, k = 0, ans = 0, gogogo;

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int max(int x, int y)
{
    return (x < y) ? y : x;
}

int dp(int t) // t = a[]'s total
{
    //cout << "dp:" << t <<endl;
    std::vector<int> f(2000, INF);
    f[0] = 0;
    for (int i = 1; i <= t; ++i)
    {
        for (int j = a[i]; j <= a[i] * n; ++j)
        {
            f[j] = min(f[j], f[j - a[i]] + 1);
        }
    }

    for (int i = a[t]; i <= a[t] * n; ++i)
    {
        if (f[i] > n)
        {
            return i - 1;
        }
    }

    return a[t] * n;
}

void dfs(int t, int y)
{
    if (k < t)
    {
        //cout <<"Final " << ++gogogo <<"\n";
        if (ans < y)
        {
            ans = y;
            for (int i = 1; i <= k; ++i)
            {
                fin[i] = a[i];
            }
        }
        return;
    }

    for (int i = a[t - 1]; i <=  y + 1; ++i)
    {
        a[t] = i;
        int yy = dp(t);
        dfs(t + 1, yy);
    }
}

int main()
{
    cin >> n >> k;
    dfs(1, 0);
    for (int i = 1; i <= k; ++i)
    {
        cout << fin[i] << " ";
    }
    cout << "\n";
    cout << "MAX=" << ans << "\n";
    return 0;
}
