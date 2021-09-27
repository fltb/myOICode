#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;
const int MAXN = 6000 + 3;

int N, V[MAXN], F[MAXN][2]/*0 choose, 1 not*/, A[MAXN];
vector<int> S[MAXN]/* b is a's son */;
void dfs(int k)
{
    //cout<<k<<endl;
    F[k][1] = 0;
    F[k][0] = V[k];
    for(int i = 0; i < S[k].size(); ++i)
    {
        //cout<<k<<" "<<i<<endl;
        int l = S[k][i];
        dfs(l);
        F[k][0] += F[l][1];
        F[k][1] += max(F[l][0],F[l][1]);
    }
}

int main()
{
    cin>>N;
    for(int i = 1; i <= N; ++i)
    {
        scanf("%d", &V[i]);
    }
    for(int i = 1; i < N; ++i)
    {
        int l,k;
        scanf("%d%d",&l,&k);
        S[k].push_back(l);
        A[l] = 1;
    }
    //cout<<111111;
    int root = 1;
    while(root <= N)
    {
        if(A[root] == 0) break;
        ++root;
    }
    //cout<<222222;
    dfs(root);
    cout<<max(F[root][0],F[root][1]);
    return 0;
}
