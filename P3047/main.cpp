#include <ios>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
int max(int a, int b)
{
    return a < b ? b : a;
}
int min(int a, int b)
{
    return a < b ? a : b;
}

const int MAXN = 100000 + 5,
          MAXK = 20 + 2;

namespace
{
    vector<int> graph[MAXN];
    int value[MAXN];
    int N, K;

    int subtreeSum[MAXN][MAXK];
    int dp[MAXN][MAXK];
}

void dfsSubtreeSum(int now, int fa)
{
    for (int i = 0; i <= K; i++)
    {
        subtreeSum[now][i] += value[now];
    }

    for (auto it = graph[now].begin(); it != graph[now].end(); ++it)
    {
        auto to = *it;
        if (to != fa)
        {
            dfsSubtreeSum(to ,now);
            for (int i = 1; i <= K; i++)
            {
                subtreeSum[now][i] += subtreeSum[to][i-1];
            }
        }
    }
}

void dfsGraphSum(int now, int fa)
{
    // bondage 0
    dp[now][0] = subtreeSum[now][0];
    // bondage 1
    dp[now][1] = subtreeSum[now][1] + dp[fa][0];
    for (int i = 2; i <= K; i++)
    {
        dp[now][i] +=  dp[fa][i-1] + subtreeSum[now][i] - subtreeSum[now][i-2];
    }
    for (auto it = graph[now].begin(); it != graph[now].end(); ++it)
    {
        auto to = *it;
        if (to != fa)
        {
            dfsGraphSum(to ,now);
        }
    }

}

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= N; i++)
    {
        int val;
        cin >> val;
        value[i] = val;
    }
    
    dfsSubtreeSum(1, 0);

    // root 
    for (int i = 0; i <= K; i++)
    {
        dp[1][i] = subtreeSum[1][i];
    }
    for (auto it = graph[1].begin(); it != graph[1].end(); ++it)
    {
        auto to = *it;
        if (to != 1)
        {
            dfsGraphSum(to, 1);
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cout << dp[i][K] << "\n";
    }
    
    return 0;
}