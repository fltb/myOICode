#include <iostream>

using namespace std;
const int MAXN = 1000 + 3;
int N, a[MAXN], f[MAXN][MAXN][2];

int main()
{
    cin>>N;
    for(int i = 1; i <= N; ++i)
    {
        cin>>a[i];
    }
    for(int i = 1; i <= N; ++i)
    {
        f[i][i][0] = 1;
    }
    for(int len = 1; len <= N; ++len)
    {
        for(int j = N; j - len > 0; --j)
        //for(int i=1,j=i+len;j<=N;i++,j++)
        {
            int i = j - len;
            /*if(A[i] < A[i+1])
            {
                F[i][j][0] += F[i+1][j][0];
            }
            if(A[i] < A[j])
            {
                F[i][j][1] += F[i][j-1][0];
            }
            if(A[j] > A[j-1])
            {
                F[i][j][0] += F[i][j-1][1];
            }
            if(A[j] > A[i])
            {
                F[i][j][1] += F[i][j-1][1];
            }*/
            if(a[i]<a[i+1])f[i][j][0]+=f[i+1][j][0];
			if(a[i]<a[j])f[i][j][0]+=f[i+1][j][1];
			if(a[j]>a[i])f[i][j][1]+=f[i][j-1][0];
			if(a[j]>a[j-1])f[i][j][1]+=f[i][j-1][1];
			f[i][j][0]%=19650827;
			f[i][j][1]%=19650827;
            //F[i][j][0] %= 19650827;
			//F[i][j][1] %= 19650827;
			//cout << "i = "<<i<<" j = "<<j<<" F[i][j][0] = "<<F[i][j][0]<<" F[i][j][1] = "<<F[i][j][1]<<endl;
        }
    }
    cout << (F[1][N][0] + F[1][N][1]) % 19650827;
    return 0;
}
