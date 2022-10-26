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
const int MAXN = 16;
int n;
int sts[MAXN + 5];
long long dp[1 << MAXN];
long long dfs(int S) {  // 被干掉的机器人的集合
    if (S == ((1 << n) - 1)) {
        return 1;  // 边界——可以消灭
    }
    if (dp[S] != -1) {
        return dp[S];
    }
    auto res = 0ll;
    auto killable = sts[0];
    for (auto weapon = 1; weapon <= n; weapon++) {
        if ((1 << (weapon - 1)) & S) {
            killable |= sts[weapon];
        }
    }
    for (auto robot = 0; robot < n; robot++) {
        if (((1 << robot) & (~S)) && ((1 << robot) & killable)) {
            res += dfs(S | (1 << robot));
        }
    }
    return dp[S] = res;
}
int main() {
    std::ios::sync_with_stdio(false);
    #ifdef FLOATINGBLOCKS
    freopen("11795.in", "r", stdin);
    freopen("11795.out", "w", stdout);
    #endif
    int T;
    cin >> T;
    for (int chesse = 1; chesse <= T; chesse++) {  // 我从 0 开始编号机器壬
        cin >> n;
        cin.get();
        for (int i = 0; i <= n; i++) {
            sts[i] = 0;
            for (int j = 0; j < n; j++) {
                char ch;
                cin >> ch;
                sts[i] |= ((ch == '1') << j);
            }
            cin.get();
        }
        for (auto i = 0; i < (1 << n); i++) {
            dp[i] = -1;
        }
        cout << "Case " << chesse << ": " << dfs(0) << '\n';
    }
    return 0;
}
/*
1
16
1111111111111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

*/