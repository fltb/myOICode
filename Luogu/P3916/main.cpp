/*
题目描述
给出NN个点，MM条边的有向图，对于每个点vv，求A(v)A(v)表示从点vv出发，能到达的编号最大的点。

输入格式
第1 行，2 个整数N,MN,M。

接下来MM行，每行2个整数U_i,V_iU
i
​
 ,V
i
​
 ，表示边(U_i,V_i)(U
i
​
 ,V
i
​
 )。点用1, 2,\cdots,N1,2,⋯,N编号。

输出格式
N 个整数A(1),A(2),\cdots,A(N)A(1),A(2),⋯,A(N)。

输入输出样例
输入 #1 复制
4 3
1 2
2 4
4 3
输出 #1 复制
4 4 3 4
说明/提示
• 对于60% 的数据，1 \le N . M \le 10^31≤N.M≤10
3
 ；

• 对于100% 的数据，1 \le N , M \le 10^51≤N,M≤10
5
 。
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const int maxn = 100000+3;
struct Node
{
    vector<int> next;

}graph[maxn];
int m,n;

int vis[maxn],
    ans[maxn];
void dfs (int x,int aaa)
{
    //cout<<"in dfs x = "<<x<<endl;
    if(vis[x] == -1)
    {
        return;
    }
    if(ans[x] != 0)
    {
        return;
    }

    ans[x] = aaa;

    vis[x] = -1;
    for(int i = 0;i < graph[x].next.size(); ++i)
    {
        dfs(graph[x].next[i],aaa);
    }
    vis[x] = 0;
}
int main()
{
    cin>>n>>m;
    for(int i = 0;i < m; ++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        graph[v].next.push_back(u);
    }

    for(int i = n;i >= 1; --i)
    {
        dfs(i,i);
    }
    for(int i = 1; i<= n; ++i)
    {
        cout<<ans[i]<<" ";
    }
    return 0;
}
/*
const int maxn = 100000+3;

struct Node
{
    vector<int> next;
    int cur;///Dont forget to set the cur value as next.size()!!!
}graph[maxn];

int m,n,
    DfsReturned[maxn];

int dfs (int x)
{
    if(DfsReturned[x] > 0)
        return DfsReturned[x];
    int maxx = x;
    while (graph[x].cur > 0)
    {
        --graph[x].cur;
        maxx = max(maxx,dfs(graph[x].next[ graph[x].cur ]));
    }
    return DfsReturned[x] = maxx;
}
int main()
{
    cin>>n>>m;
    for(int i = 0;i < m; ++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        graph[v].next.push_back(u);
    }

    for(int i = 1;i <= n; ++i)
    {
        graph[i].cur = graph[i].next.size();
    }

    for(int i = 1;i <= n; ++i)
    {
        dfs(i);
    }
    cout<<DfsReturned[1];
    for(int i = 2; i<= n; ++i)
    {
        cout<<" "<<DfsReturned[i];
    }
    cout<<endl;
    return 0;
}
*/
