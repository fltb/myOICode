#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
const int MAXR = 1000 + 2,
           INF_MIN = -0x7fffffff,
           INF_MAX = 0x7fffffff;

int graph[MAXR][MAXR],
    r,
    vis_dfs[MAXR][MAXR];

int dfs (int line, int row)
{
    if(vis_dfs[line][row] != -1)
    {
        return vis_dfs[line][row];
    }
    if(line > r)
    {
        return 0;
    }
    int maxv = INF_MIN;
    maxv = max( dfs(line + 1, row), dfs(line + 1, row + 1) );
    return vis_dfs[line][row] =  maxv + graph[line][row];
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>r;
    for(int i = 1; i <= r; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            cin>>graph[i][j];
        }
    }
    memset(vis_dfs, -1, sizeof(vis_dfs));
    dfs(1,1);
    cout<<vis_dfs[1][1];
    return 0;
}
