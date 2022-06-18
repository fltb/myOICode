#include <iostream>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
typedef __int128_t ll;
const int MAXN = 30 + 2,
          MOD  = 998244353;

int count(ll x)
{
    int cnt = 0;
    while (x)
    {
        x -= (-x & x);
        ++cnt;
    }
    return cnt;
}

int n, m, k,
    arr[MAXN];

ll sums[MAXN][MAXN],
   quan[MAXN][MAXN],
   quan_pow_sum[MAXN][MAXN];

int main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
    }

    for (int len = 2; len <= n; ++len)
    {
        for (int i = 1; i + len - 1 <= n; ++i)
        {
            int j = i + len - 1;
            
            int q = quan_pow_sum[i + 1][j] + (1 << quan_pow_sum[i][j]);
            
        }
    }

}