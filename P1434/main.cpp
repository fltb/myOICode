#include <iostream>
#include <cmath>
#include <algorithm>

#define INF 0x7fffffff

using namespace std;
const int MAXN = 100 + 2;

const int dx[] = { 0, 0, 1,-1},
           dy[] = { 1,-1, 0, 0};

int graph[MAXN][MAXN],
    dfs_vis[MAXN][MAXN],
    row,column;


int dfs (int r,int c)
{
    if(dfs_vis[r][c] != 0)
    {
        return dfs_vis[r][c];
    }

    dfs_vis[r][c] = 1;

    for(int i=0;i<4;i++)
    {
        int xx = dx[i] + r;
        int yy = dy[i] + c;
        if(xx > 0 && yy > 0 && xx <= row && yy <= column && graph[r][c] > graph[xx][yy])
        {
            dfs(xx,yy);
            dfs_vis[r][c] = max(dfs_vis[r][c],dfs_vis[xx][yy] + 1);
        }
    }
    return dfs_vis[r][c];


}

int main()
{
    cin>>row>>column;
    for(int i = 1;i <= row; ++i)
    {
        for(int j = 1;j <= column; ++j)
        {
            cin>>graph[i][j];
        }
    }
    int vvv = -INF;
    for(int i = 1;i <= row; ++i)
    {
        for(int j = 1;j <= column; ++j)
        {
            vvv = max(vvv,dfs(i,j));
        }
    }
    cout<<vvv;
    return 0;
}
