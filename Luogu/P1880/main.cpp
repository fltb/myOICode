#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 200 + 4, INF = 0x7fffffff ;

int N, A[MAXN], Sum[MAXN], DfsR[MAXN][MAXN], DfsR2[MAXN][MAXN];

int Dfs(int First, int Last)
{
    if(DfsR[First][Last] != -1)
    {
        return DfsR[First][Last];
    }
    if(First == Last)
    {
        return DfsR[First][Last] = 0;
    }
    int Best = -INF;
    for(int i = First;i < Last; ++i)
    {
        Best = max(Best, Dfs(First,i) + Dfs(i + 1, Last) + (Sum[Last] - Sum[First-1]) );
    }
    return DfsR[First][Last] = Best;
}

int Dfs2(int First, int Last)
{
    if(DfsR2[First][Last] != -1)
    {
        return DfsR2[First][Last];
    }
    if(First == Last)
    {
        return DfsR2[First][Last] = 0;
    }
    int Best = INF;
    for(int i = First;i < Last; ++i)
    {
        Best = min(Best, Dfs2(First,i) + Dfs2(i + 1, Last) + (Sum[Last] - Sum[First-1]));
    }
    return DfsR2[First][Last] = Best;
}
int main()
{
    cin>>N;
    for(int i = 1; i <= N; ++i)
    {
        cin>>A[i];
        A[i+N] = A[i];
    }
    memset(DfsR, -1, sizeof(DfsR) );
    memset(DfsR2,-1, sizeof(DfsR2));

    for(int i = 1; i <= N<<1; ++i)
    {
        Sum[i] = Sum[i-1] + A[i];
    }
    Dfs(1,N<<1);
    Dfs2(1,N<<1);

    int MinV = INF,
        MaxV = -INF;
    for(int i=1;i<=N;i++)
    {
        MaxV=max(MaxV,DfsR[i][i+N-1]);
        MinV=min(MinV,DfsR2[i][i+N-1]);
    }
    cout<<MinV<<endl<<MaxV<<endl;
    return 0;
}

