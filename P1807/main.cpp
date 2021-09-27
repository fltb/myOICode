#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#define INF_MIN -0x7fffffff

using namespace std;
const int maxn = 1500 + 3;

int n,m,ans[maxn],value[maxn][maxn],in[maxn];
vector<int> edge[maxn];
bool fined = false;


int dfs (int x);
void dfs_jurge(int x);

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i = 1; i <= m; ++i)
    {
        int u,v,w;
        cin>>u>>v>>w;
        if(value[u][v] == 0)
        {
            value[u][v] = w;
            edge[u].push_back(v);
            ++in[v];
        }
        else if(w >= value[u][v])
        {
             value[u][v] = w;
        }
    }
    //dfs_jurge(1);
    //if(!fined)
    //{
    //    cout<<-1;
    //    return 0;
    //}
    for(int i = 1;i < n; ++i)
    {
        if( 0 == in[i] && 1 != i)
        {
            for(int j = 0; j < edge[i].size(); ++j)
            {
                --in[edge[i][j]];
            }
        }
    }
    queue<int> BFS;
    BFS.push(1);
    while(!BFS.empty())
    {
        int u = BFS.front();BFS.pop();
        for(int i = 0;i < edge[u].size(); ++i)
        {
            const int v = edge[u][i];
            if(ans[v] < ans[u] + value[u][v]) ans[v] = ans[u] + value[u][v];
            if(--in[v] == 0) BFS.push(v);
        }
    }
    if(ans[n] != 0)
        cout<<ans[n];
    else cout<<-1;
    return 0;
}
/*
int dfs(int x)
{
    if(DfsReturned[x] >= 0)
        return DfsReturned[x];
    if(edge[x].size() == 0 && x != n)
    {
        return DfsReturned[x] = INF_MIN;
    }
    if(x == n)
    {
        return 0;
    }
    DfsReturned[x] = value[x];
    int tmp = INF_MIN;
    for(int i = 0; i < edge[x].size();++i)
    {
        tmp = max(tmp,dfs(edge[x][i]));
    }
    DfsReturned[x] += tmp;
    return DfsReturned[x];
}*/
bool dfs_jurge_ret[maxn];
void dfs_jurge(int x)
{
    if(x == n)
        fined = true;

    if(dfs_jurge_ret[x]) return;

    dfs_jurge_ret[x] = false;

    for(int i = 0; i < edge[x].size();++i)
    {
        dfs_jurge(edge[x][i]);
    }
}

