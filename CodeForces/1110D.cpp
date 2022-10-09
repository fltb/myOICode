#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <vector>
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
void update(int& a, int b) {
    a = max(a, b);
}
const int MAXN = 1000000 + 2, LEN = 3;
int cnt[MAXN];
// [当前值(roll)] [作为第几位] [选择几个作为 liner (剩下就是 solid)] = 当前最多的值
int dp[2][3][MAXN];
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }
    for (int j = 0; j < LEN; j++) {
        for (int i = 0; i <= max(cnt[0], cnt[1]); i++) {
            dp[0][j][i] = -1;
        }
    }
    auto ans = 0;
    for (int a = 1; a <= m; a++) {
        auto now = a & 1, pre = (a + 1) & 1;
        // 重新初始化，覆盖
        for (int j = 0; j < LEN; j++) {
            for (int i = 0; i <= max(cnt[a], cnt[a + 1]); i++) {
                dp[now][j][i] = -1;
            }
        }
        // 从上个状态转移过来，就是从之前所有状态转移到从现在开始，只有一个状态可以选择，所以选最大
        int mx = 0;
        for (int c = 0; c <= cnt[a - 1]; c++) {
            for (int idx = 0; idx < LEN; idx++) {
                update(mx, dp[pre][idx][c]);
            }
        }
        for (int c = 0; c <= cnt[a]; c++) {
            dp[now][0][c] = mx + (cnt[a] - c) / LEN;  // 加上将当前作为 solid 的贡献
        }
        for (int idx = 1; idx < LEN; idx++) {
            for (int c = 1; c <= cnt[a]; c++) {
                dp[now][idx][c] = -1;
                if (dp[pre][idx - 1][c] != -1) {
                    update(dp[now][idx][c], dp[pre][idx - 1][c] + (cnt[a] - c) / LEN);
                }
            }
        }
        for (int c = 0; c <= cnt[a]; c++) {
            if (dp[now][LEN - 1][c] != -1) {
                dp[now][LEN - 1][c] += c;  // 前面的的加过了
            }
        }
        // 还有一个方程，是当前如果有能够接上 c 个 liner 的时候，其余的同级的 c' < cnt[a] - c 的都可以加上它，不过互斥
        // 加上这个的时候还要减去之前的重复状态啊啊啊if
        mx = 0;
        for (int c = 1; c <= cnt[a]; c++) {
            if (dp[now][LEN - 1][c] != -1) {
                update(mx, c);  // 不知道对不对管他呢
            }
            for (int idx = 1; idx < LEN - 1; idx++) {
                auto cnow = cnt[a] - c;
                if (cnt[a - 1] - cnow >= c) { // 剪掉这个还能满足
                    dp[now][idx][cnow] += mx;
                }
            }
        }
        for (int idx = 0; idx < LEN; idx++) {
            for (int c = 0; c <= cnt[a]; c++) {
                update(ans, dp[now][idx][c]);
                ans = ans;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
/*
12 6
1 2 3 3 3 3 3 3 3 4 5 5
*/