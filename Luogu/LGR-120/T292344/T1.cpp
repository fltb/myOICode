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
/*const int MAXN = 100 + 1;
long long dp[MAXN][MAXN];
long long dfs(int n, int m) {
    auto& dd = dp[n][m];
    if (n == m && n == 1) {
        return 0;
    } else if (dd) {
        return dd;
    }
    dd = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i < n; i++) {
        dd = min(dd, dfs(i, m) + dfs(n - i, m) + 1);
    }
    for (int i = 1; i < m; i++) {
        dd = min(dd, dfs(n, i) + dfs(n, m - i) + 1);
    }
    return dd;
}
int main() {
    std::ios::sync_with_stdio(false);
    #ifdef FLOATINGBLOCKS
    freopen("ou", "w", stdout);
    for (int i = 1; i < MAXN;i++){
        cout << "i= " << i << '\n';
        for (int j=1; j <= i;j++) {
            cout << "    j=" << j << ' ' << dfs(i,j) << std::endl;
        }
    }
    #endif
    return 0;
}*/
int main() {
    long long n, m;
    cin >> n >> m;
    cout << n * m - 1 << '\n';
    return 0;
}