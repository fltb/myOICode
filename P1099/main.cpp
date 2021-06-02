/*
Haven't finished yet ...
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::scanf;
using std::printf;

const int MAXN = 300 + 2;

struct Node
{
    int to, val;
};

int n, s, dis[MAXN];
std::vector<Node> Edge[MAXN];


//找直径的 dfs
bool vis[MAXN];
int dis[MAXN];
void dfs(int x)
{
     for(std::vector<Node>::iterator it = Edge[x].begin(); it != Edge[x].end(); ++it)
     {
         if(!vis[it->to])
         {
             vis[it->to] = true;
             dis[it->to] = dis[x] + it->val;
             dfs(it->to);
         }
     }
}



int main()
{
    cin >> n >> s;
    for (int i = 1; i < n; ++i)
    {
        int u, v, val;
        scanf("%d%d%d", &u, &v, &val);
        Node t1, t2;
        t1.to = v, t1.val = val;
        t2.to = u, t2.val = val;
        Edge[u].push_back(t1);
        Edge[v].push_back(t2);
    }


}
