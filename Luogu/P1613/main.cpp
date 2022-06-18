#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN =  50 + 2;

int N,M,
    Dis[MAXN][MAXN];

bool G[MAXN][MAXN][64];

bool Check2k(long long X)
{
    int L = 0, R = 64;
    int M = (L+R)/2;
    long long t = 1;
    while(L <= R)
    {
        M = (L+R)/2;
        if(X == t<<M)
        {
            return true;
        }
        if(X < t<<M)
        {
            R = M - 1;
        }
        else
        {
            L = M + 1;
        }
        //cout<<M<<endl;
        //++N;
        //if(N == 30){N=0;break;}
    }
    if(X == 1<<M)return true;
    return false;
}

int main()
{
    cin >> N >> M;
    memset(Dis,0x3f,sizeof(Dis));
    for(int i = 0; i < M; ++i)
    {
        int U,V;
        cin >> U >> V;
        Dis[U][V] = 1;
        G[U][V][0] = true;
    }

    for(int idx = 1; idx < 64; ++idx)
    {
        for(int k = 1; k <= N; ++k)
        {
            for(int i = 1; i <= N; ++i)
            {
                for(int j = 1; j <= N; ++j)
                {
                    if(G[i][k][idx-1] && G[k][j][idx-1])
                    //if(Check2k(Dis[i][k] + Dis[k][j]))
                    {
                        Dis[i][j] = 1;
                        G[i][j][idx] = true;
                    }
                }
            }
        }
    }

    for(int k = 1; k <= N; ++k)
    {
        for(int i = 1; i <= N; ++i)
        {
            for(int j = 1; j <= N; ++j)
            {
                    Dis[i][j] = min(Dis[i][j], Dis[i][k] + Dis[k][j]);
            }
        }
    }

    cout << Dis[1][N];

    return 0;
}
