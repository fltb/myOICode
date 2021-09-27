#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
const int MAXN = 2*(100 + 2), INF = 0x7fffffff;

int f[MAXN][MAXN], A[MAXN], N;

int dp(int l,int r)
{
    int ans=0;
    if(f[l][r]!=0) return f[l][r];
    if(l==r-1) return A[l]*A[r]*A[r+1];
    for(int k=l;k<r;k++)
    {
        ans=max(ans,dp(l,k)+dp(k+1,r)+A[l]*A[k+1]*A[r+1]);
    }
    return f[l][r]=ans;
}


int main()
{
    cin >> N;
    for(int i = 1; i <= N; ++i)
    {
        cin >> A[i];
        A[i+N] = A[i];
    }
    A[N<<1+1] = A[1];
    //memset(F, -1, sizeof(F));


    int Ans = -INF;
    for(int i = 1; i <= N; ++i)
    {
        Ans = max(Ans,dp(i,i+N-1));
    }
    cout<<Ans;
    return 0;
}
