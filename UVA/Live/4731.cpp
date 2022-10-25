#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <tuple>
#include <vector>
#define cosnt const
using std::cin;
using std::cout;
using std::function;
using std::vector;
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
const int MAXN = 1e4 + 2;
const double INFD = 1e12 + 2;
int n, m;
// 转移？当前已经选择了后面的最小的话，要和前面拼接，需要乘上去的那个值无法判断
// 考虑前面全部搞好之后和后面拼接
// dp[i][j] [0:i+1][j 刀] 的最小期望 Sum 前缀和 a 降序排序
double dp[MAXN][MAXN], sum[MAXN], a[MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        std::sort(&a[1], &a[n + 1], std::greater<double>());
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + a[i];
            for (int j = 1; j <= n; j++) {
                dp[i][j] = INFD;
            }
        }
        for (int i = 1; i <= n; i++) {
            dp[i][1] = i * sum[i];
            for (int j = 2; j <= min(m, i); j++) {
                for (int k = i - 1; k >= min(1, j - 1); k--) {
                    dp[i][j] = min(dp[i][j], dp[k][j - 1] + i * (sum[i] - sum[k]));
#ifdef FLOATINGBLOCKS
                    if (dp[i][j] <= 0) {
                        cout << i << ' ' << j << ' ' << dp[i][j] << std::endl;
                    }

#endif
                }
#ifdef FLOATINGBLOCKS
                cout << i << ' ' << j << ' ' << dp[i][j] << std::endl;
#endif
            }
        }
        cout << std::setprecision(4) << std::fixed << dp[n][m] / sum[n] << '\n';
    }
    return 0;
}