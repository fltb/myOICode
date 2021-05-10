#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
const int MAXN = 20 + 2;

int cellar [MAXN] ,n ,vis[MAXN],Next[MAXN];
vector<int> cont [MAXN];

int dfs (int x)
{
    if(vis[x] != 0)
    {
        return vis[x];
    }
    int value = 0, to = -1;
    for(int i = 0; i < cont[x].size(); ++i)
    {
        int go = cont[x][i];
        vis[go] = dfs(go);
        if(value <vis[go])
        {
            value = vis[go];
            to = go;
        }
    }
    Next[x] = to;
    return vis[x] = value + cellar[x];
}

int main()
{
    cin>>n;
    for(int i = 1;i <= n; ++i)
    {
        cin>>cellar[i];
    }
    for(int i = 1;i <= n; ++i)
    {
        for(int j = i + 1;j <= n; ++j)
        {
            int a;
            cin>>a;
            if(a == 1)
            {
                cont[i].push_back(j);
            }
        }
    }
    int v = 0, maxv = 0,to = -1;
    for(int i = 1; i <= n; ++i)
    {
        v = dfs(i);
        if(maxv < v)
        {
            maxv = v;
            to = i;
        }
    }
    while(to != -1)
    {
        cout<<to<<" ";
        to = Next[to];
    }
    cout<<endl<<maxv;

    return 0;
}
