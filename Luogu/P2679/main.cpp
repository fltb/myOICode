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
const int MAXN = 1000 + 2, MAXM = 200 + 2, MOD = 1000000007;
/*
考虑 dp
让我们先定义状态
    dp[a当前下标][b当前下标][分出来几段][当前是否匹配] = 几种方法
  转移？
    我先看下之前已经到了第几位，枚举 bi
        然后枚举分出来的段数 ci
            a[ai] == b[bi]
                说明对答案有新的贡献
                dp[ai][bi][ci][1] += dp[ai-1][bi-1][ci-1][0] + dp[ai-1][bi][ci][1]
            a[ai] != b[bi]
                那就是没有啥用处，直接赋值上面的值好了
                对了，清空之前的末尾的 1

*/
long long dp[2][MAXM][MAXM][2];
int a[MAXN], b[MAXM];
int main() {
    std::ios::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        char ch;
        cin >> ch;
        a[i] = (int)ch;
    }
    cin.get();
    for (int i = 1; i <= m; i++) {
        char ch;
        cin >> ch;
        b[i] = (int)ch;
    }
    dp[0][0][0][0] = dp[1][0][0][0] = 1;
    for (int ai = 1; ai <= n; ai++) {
        for (int bi = 1; bi <= min(ai, m); bi++) {
            for (int ci = 1; ci <= min(bi, k); ci++) {
                auto cn = ai & 1, cp = (ai - 1) & 1;
                if (a[ai] == b[bi]) {  // 当前匹配的时候
                    // 当前              之前紧接着的匹配           紧接着的不匹配               匹配但是我就是切掉怎么着
                    dp[cn][bi][ci][1] = dp[cp][bi - 1][ci][1] + dp[cp][bi - 1][ci - 1][0] + dp[cp][bi - 1][ci - 1][1];
                } else {
                    dp[cn][bi][ci][1] = 0;
                }
                // 当前不选择         之前不选择            之前选择
                dp[cn][bi][ci][0] = dp[cp][bi][ci][0] + dp[cp][bi][ci][1];
                dp[cn][bi][ci][1] %= MOD;
                dp[cn][bi][ci][0] %= MOD;
            }
        }
    }
    cout << (dp[n & 1][m][k][0] + dp[n & 1][m][k][1]) % MOD << '\n';
    return 0;
}