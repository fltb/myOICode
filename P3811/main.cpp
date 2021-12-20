#include <algorithm>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using ll = long long;

const int MAXN = 3 * 1000000 + 2;
ll inv[MAXN];

ll fpm(ll a, ll b)
{
    a %= b;
    ll p = b - 2,
       ans = 1ll;
    while (p)
    {
        if (p & 1)
        {
            ans *= a;
            ans %= b;
        }
        a *= a;
        a %= b;
        p >>= 1;
    }
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    ll n, p;
    cin >> n >> p;

    inv[1] = 1;
    for (ll i = 2; i <= n; ++i)
    {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
    
    for (ll i = 1; i <= n; ++i)
    {
        cout << inv[i] << "\n";
    }

    return 0;
}