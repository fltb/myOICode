#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
int max(int a, int b)
{
    return a < b ? b : a;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
const int MOD = 1000000000 + 7,
          MAXN = 100 + 2;

struct Matrix
{																	
	long long mt[MAXN][MAXN];
} ans, in;

long long n,k;
Matrix operator*(const Matrix &x,const Matrix &y)
{
	Matrix a;
	for(int i = 1; i <= n; i++)
    {
		for(int j = 1; j <= n; j++)
        {
            a.mt[i][j] = 0;
        }
    }
	for(int i = 1; i <= n; i++)
	{
        for(int j = 1; j <= n; j++)
        {
			for(int k = 1; k <= n; k++)
            {
				a.mt[i][j] += x.mt[i][k] * y.mt[k][j] % MOD;
				a.mt[i][j] %= MOD;
			}
        }
    }
	return a;
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> in.mt[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        ans.mt[i][i]=1;
    }
    while (k > 0)
    {
        if (k & 1)
        {
            ans = ans * in;
        }
        in = in * in;
        k >>= 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << ans.mt[i][j] << " ";
        }
        cout << "\n";
    }
}