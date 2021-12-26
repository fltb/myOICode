#include <iostream>
#include <utility>
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using ll = long long;

pair<ll, ll> exgcd(ll a, ll b)
{
    if (b == 0ll)
    {
        return make_pair(1ll, 0ll);
    }  
    auto ans = exgcd(b, a % b);
    ll x = ans.second;
    ll y = ans.first - (a / b) * ans.second;
    return make_pair(x, y);
}

ll gcd(ll a, ll b)
{
    return b > 0ll ? gcd(b, a % b) : a;
}

int main()
{
    ll x, y, m, n, l;
    cin >> x >> y >> m >> n >> l;
    ll a = n - m,
       b = l,
       c = x - y;

    if (a < 0ll)
    {
        a = -a;
        c = -c;
    }

    ll k = exgcd(a, b).first;
    ll g = gcd(a, b);

    if (c % g)
    {
        cout << "Impossible\n";
    }
    else
    {
        ll md = b / g;
        ll fc = c / g;
        ll ans = ((k * fc) % md + md) % md;
        cout << ans << "\n";
    }
    return 0;
}