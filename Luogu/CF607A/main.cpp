#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const;
using std::cin;
using std::cout;
using std::lower_bound;
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
const int MAXN = 100000 + 2;
int ps[MAXN], ls[MAXN];
int disable[MAXN];
int dp[MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ps[i] >> ls[i];
    }
    for (int i = 1; i < n; i++) {
        int cur = lower_bound(ps, ps + i, ps[i] - ls[i]) - ps;
        disable[i] = i - cur + int(ps[i] - ls[i] > ps[cur]);
    }
    // 不摧毁当前的，当前剩下多少塔 dp[i]
    dp[0] = 1;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - disable[i] - 1] + 1;
    }
    // 最后枚举答案
    auto ans = 0x7fffffff;
    for (int i = 0; i < n; i++) {
        ans = min(ans, (i + 1 - dp[i]) + n - i - 1);
    }
    cout << ans << '\n';
    return 0;
}