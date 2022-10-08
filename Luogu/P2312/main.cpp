#include <algorithm>
#include <cstdio>
#include <ctime>
#include <ios>
#include <iostream>
#include <locale>
#include <random>
#define cosnt const;
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
const int MAXN = 100 + 2;
const int MODS[] = {10000723,
                     10000591,
                     10000591,
                     10000769,
                     10000223,
                     10000103,
                     10000763,
                     10000733,
                     10000723,
                     10000721,
                     10000691,
                     10000849};  // 数学题目和七个大质数的故事~
long long red(int MOD) {
    int f = 0, c = std::getchar();
    long long t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, t %= MOD, c = std::getchar();
    if (f)
        t = -t;
    return t;
}
long long a[MAXN];
long long ans[MAXN], cnt;
int main() {
    std::ios::sync_with_stdio(false);
    srand(std::time(0) + 114);
    auto md = rand() % 12;
    const auto MOD = MODS[md];
    int n, m;
    read(n), read(m);

    for (int i = 0; i <= n; i++) {
        a[i] = red(MOD);
    }

    for (int x = 1; x <= m; x++) {
        long long cal = 0;
        for (int i = n; i >= 1; i--) {
            cal = (a[i] + cal) * x % MOD;
        }
        if ((cal + a[0]) % MOD == 0) {
            ans[++cnt] = x;
        }
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}