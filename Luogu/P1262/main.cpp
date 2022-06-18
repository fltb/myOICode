#include <iostream>
#include <vector>
#include <stack>
using std::cin;
using std::cout;
using std::endl; 
using std::vector;
using std::stack;
const int MAXN = 3000 + 2;
int min(int a, int b)
{
    return a < b ? a : b;
}

vector<int> graph[MAXN], father[MAXN];
int money[MAXN];

// for trojan
int vis[MAXN], dfn[MAXN], low[MAXN],vals[MAXN],
    belongs[MAXN], in_stack[MAXN], idx, cnt;
vector<int> group[MAXN];
stack<int> stck;
void tarjan(int u)
{
    dfn[u] = low[u] = ++idx;
    stck.push(u);
    in_stack[u] = 1;
    for (size_t i = 0; i < graph[u].size(); ++i)
    {
        int v = graph[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v])
        {
            low[u] = min(low[u], low[v]);
        }
    }
    if (dfn[u] == low[u])
    {
        ++cnt;
        int v, cost = 0;
        do
        {
            v = stck.top();
            stck.pop();
            group[cnt].push_back(v);
            belongs[v] = cnt;
            in_stack[v] = 0;
            if (money[v])
            {
                if (cost)
                {
                    cost = min(cost, money[v]);
                }
                else 
                {
                    cost = money[v];
                }
            }
        } while (v != u);
        vals[cnt] = cost;
    }
}

// construct graph2

int indegree[MAXN];

void construct_new_graph()
{
    for (int i = 1; i <= cnt; ++i)
    {
        int u = group[i][0];
        for (size_t j = 0; j < group[i].size(); ++j)
        {
            if (dfn[group[i][j]] == low[group[i][j]])
            {
                u = group[i][j];
            }
        }
        for (size_t j = 0; j < graph[u].size(); ++j)
        {
            int v = graph[u][j];
            if (belongs[v] != belongs[u])
            {
                ++indegree[belongs[v]];
            }
        }
    }
}


int main()
{
    int n, p; 
    cin >> n >> p;
    for (int i = 1; i <= p; ++i)
    {
        int x, val;
        cin >> x >> val;
        money[x] = val;
    }
    int r;
    cin >> r;
    for (int i = 1; i <= r; ++i)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        father[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) 
    {
        if (!dfn[i] && money[i])
        {
            tarjan(i);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!dfn[i])
        {
            cout << "NO\n" << i << "\n";
            return 0;
        }
    }
    construct_new_graph();
    int ans = 0;
    for (int i = 1; i <= cnt; ++i)
    {
        if (indegree[i] == 0)
        {
            ans += vals[i];
        }
    }
    
    cout << "YES\n" << ans << "\n";
}
