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
const int MODS[] = {
    10433,
    100000399,
    1000000403,
};  // 数学题目和几个大质数的故事~
void red(long long& t1, long long& t2, long long& t3) {
    int f = 0, c = std::getchar();
    t1 = t2 = t3 = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t1 = t1 * 10 + c - 48, t1 %= MODS[0], t2 = t2 * 10 + c - 48, t2 %= MODS[1], t3 = t3 * 10 + c - 48, t3 %= MODS[2], c = std::getchar();
    if (f)
        t1 = -t1, t2 = -t2, t3 = -t3;
}
long long a[MAXN][3];
long long ans[MAXN], cnt;
int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    read(n), read(m);

    for (int i = 0; i <= n; i++) {
        red(a[i][0], a[i][1], a[i][2]);
    }

    for (int x = 1; x <= m; x++) {
        bool is = true;
        for (int m = 0; m < 2; m++) {
            long long cal = 0;
            for (int i = n; i >= 1; i--) {
                cal = (a[i][m] + cal) * x % MODS[m];
            }
            if ((cal + a[0][m]) % MODS[m] != 0) {
                is = false;
                break;
            }
        }
        if (is) {
            ans[++cnt] = x;
        }
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}