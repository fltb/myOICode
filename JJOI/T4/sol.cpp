#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const
using std::cin;
using std::cout;
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
const int MAXM = 1000 + 2;
struct Poi {
    long long p, l;
    Poi(int pp = 0, int ll = 0) : p(pp), l(ll) {}
};
Poi ps[MAXM];
long long ans = 0;
int main() {
    std::ios::sync_with_stdio(false);
    long long n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int p, l;
        cin >> p >> l;
        ps[i] = Poi(p, l);
    }
    std::sort(&ps[1], &ps[m + 1], [](const Poi& a, const Poi& b) {
        return a.p < b.p;
    });
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j++) {
            if (ps[i].l > ps[j].l) {
                ans++;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        ans += (n - ps[i].p - 1 - (m - i));
    }
    cout << ans << '\n';
    return 0;
}
/*
5 2
3 2
2 4
*/