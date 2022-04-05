#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::vector;
using std::cout;
typedef long long ll;
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
const int MAXN = 1e5 + 2, MAXK = 100 + 2, MOD = 1000000007;

inline int add(ll x,ll y){
    x %= MOD;
    y %= MOD;
    return (int)(x + y)%MOD;
}

/***********

  有无 影响
dp[0][0] 
dp[1][0] 
dp[0][1] 
dp[1][1] 
***********/
int dp[MAXN][MAXK][2][2] { 0 };
ll tmp[MAXK][2][2] { 0ll };
int n, m, size[MAXN] {0};
vector<int> edges[MAXN];

void dfs(int now, int fa)
{
    size[now] = 1;
    dp[now][1][1][0] = 1;
    dp[now][0][0][0] = 1;

    for (int to : edges[now])
    {
        if (to == fa)
        {
            continue;
        }
        dfs(to, now);
        for (int i = 0; i <= min(size[now], m); i++)
        {
            for (int j = 0; j <= 1; j++)
            {
                for (int k = 0; k <= 1; k++)
                {
                    tmp[i][j][k] = dp[now][i][j][k];
                    dp[now][i][j][k] = 0;
                }
            }
        }
        for (int i = 0; i <= min(size[now], m); i++)
        {
            for (int j = 0; j <= min(size[to], m - i); j++)
            {
                dp[now][i + j][0][0] = add(dp[now][i + j][0][0], (ll)tmp[i][0][0] * (ll)dp[to][j][0][1] % MOD);

                dp[now][i + j][0][1] = add(dp[now][i + j][0][1], (ll)tmp[i][0][1] * (ll)((ll)dp[to][j][0][1] + (ll)dp[to][j][1][1]) % MOD);
                dp[now][i + j][0][1] = add(dp[now][i + j][0][1], (ll)tmp[i][0][0] * (ll)dp[to][j][1][1] % MOD);

                dp[now][i + j][1][0] = add(dp[now][i + j][1][0], (ll)tmp[i][1][0] * (ll)((ll)dp[to][j][0][0] + (ll)dp[to][j][0][1]) % MOD);

                dp[now][i + j][1][1] = add(dp[now][i + j][1][1], (ll)tmp[i][1][1] * (ll)((ll)dp[to][j][1][1] + (ll)dp[to][j][0][1] + (ll)dp[to][j][1][0] + (ll)dp[to][j][0][0]) % MOD);
                dp[now][i + j][1][1] = add(dp[now][i + j][1][1], (ll)tmp[i][1][0] * ((ll)dp[to][j][1][1] + (ll)dp[to][j][1][0]) % MOD);
            }
        }
        size[now] += size[to];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    dfs(1, -1);
    cout << (dp[1][m][0][1] + dp[1][m][1][1]) % MOD << "\n";
    return 0;
}