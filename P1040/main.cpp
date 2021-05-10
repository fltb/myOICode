#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
/*const int MAXN = 30 + 3;

long long DfsReturned[MAXN][MAXN][MAXN];
int Tree[MAXN],RootTo[MAXN][MAXN][2];

int dfs(int LeftEdge, int Root, int RightEdge,int Cur)
{
    if(DfsReturned[LeftEdge][Root][RightEdge] != -1)
    {
        return DfsReturned[LeftEdge][Root][RightEdge];
    }

    if(LeftEdge >= RightEdge)
    {
        return 1;
    }

    int left = 1,right = 1;

    for(int i = LeftEdge;i < Root; ++i)
    {
        if(left < dfs(LeftEdge, i , Root - 1,Cur))
        {
            left = dfs(LeftEdge, i, Root - 1,Cur);
            RootTo[Cur][Root][0] = i;
        }
    }
    for(int i = Root + 1;i <= RightEdge; ++i)
    {
        if(right < dfs(Root + 1, i, RightEdge,Cur))
        {
            right = dfs(Root + 1, i, RightEdge,Cur);
            RootTo[Cur][Root][1] = i;
        }
    }
    return (LeftEdge < RightEdge) ? (DfsReturned[LeftEdge][Root][RightEdge] = left * right + Tree[Root]) : (DfsReturned[LeftEdge][Root][RightEdge] = 1);
}

int main()
{
    memset(DfsReturned,-1,sizeof(DfsReturned));
    int n;
    cin>>n;
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d",&Tree[i]);
    }

    int Best = 0,BestCur = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(Best < dfs(1,i,n,i))
        {
            Best = dfs(1,i,n,i);
            BestCur = i;
        }
    }

    cout<<Best<<"\n"<<BestCur;

    return 0;
}
*/

const int MAXN = 50 + 2;

long long n, DP[MAXN][MAXN], Root[MAXN][MAXN];

void PrtAns (long long x1,long long x2)
{
    if(x1 > x2)
    {
        return;
    }
    printf("%lld ",Root[x1][x2]);
    PrtAns(x1, Root[x1][x2] - 1);
    PrtAns(Root[x1][x2] + 1, x2);
}

int main()
{
    cin>>n;
    for(int i = 1; i <= n; ++i)
    {
        scanf("%lld",&DP[i][i]);
        DP[i][i-1] = 1;
        Root[i][i] = i;
    }

    for(int i = n; i >= 1; --i)
    {
        for(int j = i + 1;j <= n; ++j)
        {
            for(int k = i; k <= j; ++k)
            {
                if(DP[i][j] < (DP[i][k - 1] * DP[k + 1][j] + DP[k][k]) )
                {
                    DP[i][j] = DP[i][k - 1] * DP[k + 1][j] + DP[k][k];
                    Root[i][j] = k;
                }
            }
        }
    }

    cout<<DP[1][n]<<endl;

    PrtAns(1,n);

}
