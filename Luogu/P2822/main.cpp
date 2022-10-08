#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
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
const int MAXN = 2000 + 2;
/*
组合数字不停 MOD K，然后用容斥来 DP 吧。
*/
int C[MAXN][MAXN], dp[MAXN][MAXN];
void initAC(int, int);
int main() {
    std::ios::sync_with_stdio(false);
    int t, k;
    cin >> t >> k;
    initAC(t, k);
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << dp[n][min(n, m)] << '\n';
    }
    return 0;
}
void initAC(int n, int k) {
    C[1][0] = C[1][1] = C[0][0] = 1;
    for (int i = 2; i <= MAXN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % k;
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1] + (C[i][j] % k == 0);
        }
        dp[i][i + 1] = dp[i][i];
    }
}
