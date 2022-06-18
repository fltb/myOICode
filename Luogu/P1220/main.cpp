#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
const int MAXN = 50+3, INF = 0x7fffffff;
enum WhereTheManAt {LEdge = 0, REdge = 1};

struct Light
{
    int Locate;
    int PowerSum;
    Light(){  Locate = 0; PowerSum = 0;}
    bool operator<(const Light& x)const{
        return Locate < x.Locate;
    }
}A[MAXN];

int F[MAXN][MAXN][2], N, C;

int GetSub(const Light & X, const Light & Y)
{
    return X.PowerSum - Y.PowerSum;
}

int GetDis(const Light & X, const Light & Y)
{
    return X.Locate - Y.Locate;
}

int GetCal(int LE, int RE, int I, int J)
{
    int Sub = GetSub(A[LE-1],A[0]) + GetSub(A[N],A[RE]),
        Dis = GetDis(A[J],A[I]);
    return Sub * Dis;
}

int main()
{
    cin>>N>>C;
    for(int i = 1; i <= N; ++i)
    {
        int Pow;
        scanf("%d%d",&A[i].Locate,&Pow);
        A[i].PowerSum = A[i-1].PowerSum + Pow;
    }
    memset(F,0x3f,sizeof(F));
    F[C][C][REdge] = 0;
    F[C][C][LEdge] = 0;

    //cout<<GetCal(2,4,2,3)<<endl;
    //cout<<GetCal(2,3,2,3)<<endl;

    for(int R = C; R <= N; ++R)
    {
        for(int L = R-1; L > 0; --L)
        {
            F[L][R][LEdge] = min( F[L+1][R][LEdge] + GetCal(L+1,R,L,L+1), F[L+1][R][REdge] + GetCal(L+1,R,L,R) );
            F[L][R][REdge] = min( F[L][R-1][REdge] + GetCal(L,R-1,R-1,R), F[L][R-1][LEdge] + GetCal(L,R-1,L,R) );
        }
    }

    cout << min( F[1][N][LEdge], F[1][N][REdge]);


    return 0;
}
