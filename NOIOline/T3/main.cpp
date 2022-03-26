#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::map;
using std::set;
template<typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

int mp[10004][6];
int main()
{
    std::freopen("sort.in", "r", stdin);
    std::freopen("sort.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> mp[j][i];
        }
    }
    long long ans = 0;
    for (int j = 1; j <= n; j++)
    {
        std::sort(&mp[j][1], &mp[j][m]+1);
    }
    for (int i1 = 1; i1 <= n; i1++)
    {
        for (int i2= 1; i2 <= n; i2++)
        {
            if (i1 != i2)
            {
                ans += mp[i1][1] + mp[i2][1] + mp[i1][m] + mp[i2][m];
            }
        }
    }
    cout << ans;
    return 0;
}