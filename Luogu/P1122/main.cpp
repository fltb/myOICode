#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;
const int MAXN = 16000+2;

int N, T[MAXN], Ans, F[MAXN], C[MAXN];
vector<int> S[MAXN];

void dfs(int x)
{
    F[x] = T[x];
    C[x] = 1;
    for(vector<int>::iterator it = S[x].begin(); it != S[x].end(); ++it)
    {
        if(C[*it] == 0)
        {
            dfs(*it);
            F[x] += max(0,F[*it]);
        }
    }
    Ans = max(Ans,F[x]);
}

int main()
{
    cin>>N;
    for(int i = 1; i <= N; ++i)
    {
        scanf("%d",&T[i]);
    }
    for(int i = 1; i < N; ++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        S[a].push_back(b);
        S[b].push_back(a);
    }
    dfs(1);
    cout<<Ans;
    return 0;
}
