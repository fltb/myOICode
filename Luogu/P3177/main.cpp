#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
template <typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}
template <typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}
const int MAXN = 2000 + 2;
enum Costs
{
    BL = 1,
    WH = 1
};  
struct Edge
{
    int from, to, val;
    Edge(int from_=0, int to_=0, int val_=0) : from(from_), to(to_), val(val_) {}
};

vector<Edge> edges;

struct Node
{
    vector<int> eids;
};

Node graph[MAXN];
int n, m;

long long f[MAXN*2][MAXN];
int cSZ[MAXN*2];
void dfs(int eid, int fa)
{
    const Edge & E = edges[eid];
    int tid = E.to; // to id
    bool leaf = true;
    f[eid][0] = 0;
    f[eid][1] = 0;
    cSZ[eid] = 1;
    for (int ceid : graph[tid].eids)
    {
        const Edge & CE = edges[ceid];
        if (CE.to == fa) { continue; }

        dfs(ceid, CE.from);
        cSZ[eid] += cSZ[ceid];
    }
    // to bag
    for (int ceid : graph[tid].eids)
    {
        const Edge & CE = edges[ceid];
        if (CE.to == fa)
        {
            continue;
        }
        if (leaf)
        {
            leaf = false;
            for (int j = 0; j <= min(cSZ[eid], m); j++)
            {
                f[eid][j] = f[ceid][j];
            }
            continue;
        }
        for (int j = min(cSZ[eid], m); j >= 0; j--) // j is black that child tree contains
        {
            for (int k = 0; k <= min(j, cSZ[ceid]); k++)
            {
                if (f[eid][j-k] != -1) 
                {
                    f[eid][j] = max(f[eid][j], f[ceid][k] + f[eid][j-k]);
                }
            }
        }
    }
    
    if (leaf)
    {
        f[eid][0] = ((0) * (m) + (1) * (n - m - 1)) * E.val;
        f[eid][1] = ((1) * (m - 1) + (0) * (n - m)) * E.val;
    }
    else
    {
        for (int j = min(cSZ[eid], m); j > 0; j--)
        {
            const long long val = (long long)((j) * (m - j) + (cSZ[eid] - j) * (n - m - (cSZ[eid] - j))) * E.val;
            // 和这条边直接相连的点是白色或者黑色
            f[eid][j] = max(f[eid][j] + val, f[eid][j - 1] + val);
        }
        // j == 0
        const long long val = (long long)((0) * (m - 0ll) + (cSZ[eid] - 0) * (n - m - (cSZ[eid] - 0))) * E.val;
        f[eid][0] = f[eid][0] + val;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++)
    {
        int from, to, dis;
        cin >> from >> to >> dis;
        edges.push_back(Edge(from, to, dis));
        graph[from].eids.push_back(edges.size()-1);
        edges.push_back(Edge(to, from, dis));
        graph[to].eids.push_back(edges.size()-1);
    }
    std::memset(f, -1, sizeof(f));
    int preroot = edges.size();
    bool first = true;
    for (int ceid : graph[1].eids)
    {
        dfs(ceid, 1);
        if (first)
        {
            first = false;
            for (int j = 0; j <= min(cSZ[ceid], m); j++)
            {
                f[preroot][j] = f[ceid][j];
            }
            continue;
        }
        for (int j = min(n, m); j >= 0; j--) // j is black that child tree contains
        {
            for (int k = 0; k <= min(j, cSZ[ceid]); k++)
            {
                if (f[preroot][j-k] == -1)
                {
                    continue;
                }
                f[preroot][j] = max(f[preroot][j], f[ceid][k] + f[preroot][j-k]);
            }
        }
    }
    cout << max(f[preroot][m], ((m - 1 >= 0) ? f[preroot][m-1] : 0)) << "\n";
    return 0;
}