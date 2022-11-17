#include <math.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ios>
#include <iostream>
#include <tuple>
#include <unordered_map>
#define cosnt const
using std::cin;
using std::cout;
using std::get;
using std::make_tuple;
using std::tuple;
using std::unordered_map;
typedef long long ll;
template <typename T>
inline void read(T& t) {
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
template <typename T>
inline T gcv(T a, T b) {
    return b ? gcv(b, a % b) : a;
}
const ll MAXN = 1e18 + 5;
const ll LIMIT = std::pow(MAXN, 1.0 / 3) * 2;
int main() {
    std::ios::sync_with_stdio(false);
    unordered_map<ll, tuple<ll, ll>> um;
    for (auto i = 1ll; i <= LIMIT; i++) {
        auto res = i * (i + 1);
        for (auto j = i + 2;; j++) {
            res /= std::__gcd(res, j);
            if (res > MAXN / j) {
                break;
            }
            res *= j;
            if (!um.count(res)) {
                um[res] = make_tuple(i, j);
            }
        }
    }
    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        if (um.count(n)) {
            auto a = get<0>(um[n]), b = get<1>(um[n]);
            cout << a << ' ' << b << '\n';
        } else {
            ll l = 1, r = 1e9, ans = -1;
            while (l <= r) {
                auto mid = (l + r) / 2;
                if (mid * (mid + 1) > n) {
                    r = mid - 1;
                } else if (mid * (mid + 1) < n) {
                    l = mid + 1;
                } else {
                    ans = mid;
                    break;
                }
            }
            if (ans != -1) {
                cout << ans << ' ' << ans + 1 << '\n';
            } else {
                cout << "NIE\n";
            }
        }
    }
    return 0;
}