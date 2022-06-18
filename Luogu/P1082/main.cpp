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

int main()
{
    int a, b;
    cin >> a >> b;

    ll x = exgcd(a, b).first;

    x = (x % b + b) % b;
    cout << x << '\n';

    return 0;
}