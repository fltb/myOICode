#include <iostream>
#include <vector>
#include <map>

using namespace std;
const int MAXN = 300+2, INF = 0x7fffffff ;

vector<int> Son[MAXN];
int Val[MAXN], N, M,SRC[MAXN][MAXN], RC[MAXN][MAXN];

int dfs(int x, int v);
int srch(int vp, int i, int x);

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; ++i)
    {
        int a;
        cin >> a >> Val[i];
        Son[a].push_back(i);
    }

    cout << dfs(0, M+1);
    return 0;
}

int srch(int vp, int i, int x)
{
    int & SSS = SRC[vp][ Son[x][i] ];
    if(SSS)
    {
        return SSS;
    }
    if(Son[x].empty() || !vp)
    {
        return SSS = 0;
    }
    if(i == Son[x].size() - 1)
    {
        return SSS = dfs(Son[x][i], vp);
    }
    SSS = -INF;
    int cur = 0;
    while(vp>=0)
    {
        SSS = max(SSS, dfs(Son[x][i], cur) + srch(vp, i+1, x) );
        --vp,++cur;
    }
    return SSS;
}

int dfs(int x, int v)
{
    int & RRR = RC[x][v];
    if(v <= 0)
    {
        return RRR = 0;
    }
    if(Son[x].empty() || v <= 1)
    {
        return RRR = Val[x];
    }
    RRR = srch(v-1, 0, x) + Val[x];
    return RRR;
}
