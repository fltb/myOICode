#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
/*
思路：
已知： 若 gcd(a, b) == 1 则 gcd(a * p, b * p) == p (p 为质数)
*/
const int MAXN = 10 + 2;

double phi[MAXN];
long long sum[MAXN];
bool prime[MAXN];

int main()
{
    int n;
    cin >> n;
    // 先假设全部是质数
    for (int i = 1; i <= n; i++)
    {
        phi[i] = i;
        prime[i] = true;
    }
    // 1 不是质数
    prime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (prime[i])
        {
            phi[i] = i - 1;
            for (int j = 2; i * j <= n; ++j)
            {
                prime[i * j] = false;
                // v 是当前的这个数的质因数个数
                phi[i * j] *= 1.0 - 1.0 / i;
            }
        }
    }
    // 现在质数是 true，偶数 false
    sum[1] = 1ll;
    for (int i = 2; i <= n; i++)
    {
        sum[i] = sum[i - 1] + 1ll * (int(phi[i])) * 2;
    }
    long long ans = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (prime[i])
        {
            ans += sum[n / i];
        }
    }
    cout << ans << "\n";
}