#include <ios>
#include <iostream>
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
const int MAXN = 100 + 5;

vector<int> graph[MAXN];

bool rec[MAXN];
int length;
void dfs(int now, int depth)
{
    rec[now] = true;
    length = max(length, depth);
    for (auto it = graph[now].begin(); it != graph[now].end(); ++it)
    {
        int to = *it;
        if (!rec[to])
        {
            dfs(to, depth + 1);
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(0, 1);
    if (length >= k + 1)
    {
        cout << k + 1 << "\n";
    }
    else
    {
        cout << min(n, length + (k + 1 - length) / 2) << "\n";
    }
    return 0;
}