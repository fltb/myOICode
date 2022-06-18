#include <iostream>
using std::cin;
using std::cout;
using std::endl;

const int MAXN = 50+2;

int graph[MAXN][MAXN],
    f[MAXN*2][MAXN*2];

int max4 (int a, int b, int c, int d)
{
    a = a < b ? b : a;
    a = a < c ? c : a;
    a = a < d ? d : a;
    return a;
}

int main()
{
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> graph[i][j];
        }
    }

    for (int step = 3; step <= m+n; ++step)
    {
        for (int i = step - 1 < n ? step - 1 : n ; i >= 1; --i)
        {
            for (int j = i - 1; j >= 1; --j)
            {
                f[i][j] = max4(f[i][j], f[i][j-1], f[i-1][j], f[i-1][j-1]) + graph[step-i][i] + graph[step-j][j];
            }
        }
    }

    cout << f[n][n-1] << endl;
}
