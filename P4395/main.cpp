#include <iostream>
#include <vector>
#include <cstring>
using std::cin;
using std::cout;
using std::vector;
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
const int MAXN = 10000 + 2,
          LGMAXN = 16;

vector<int> graph[MAXN];
int n,
    dp[MAXN][LGMAXN];
void dfs(int now, int fa)
{
    for (int j = 1; j <= LGMAXN; j++) // child
    {
        dp[now][j] = j;
    }
    for (auto chi : graph[now])
    {
        if (chi == fa)
        {
            continue;
        }
        dfs(chi, now);
        for (int i = 1; i <= LGMAXN; i++) // now
        {
            int minn=0x3f3f3f3f;
            for (int j = 1; j <= LGMAXN; j++) // child
            {
                if (i != j)
                {
                    minn = min(minn, dp[chi][j]);
                }
            }
            dp[now][i] += minn;
        }
    }
}
int main() 
{
    cin >> n;
    for (int i = 0; i < n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    std::memset(dp, 0x3f3f3f, sizeof(dp));
    dfs(1, 0);
    int ans = 2147483647;
    for (int i = 1; i <= LGMAXN; i++)
    {
        ans = min(ans, dp[1][i]);
    }
    cout << ans << "\n";
    return 0;
}