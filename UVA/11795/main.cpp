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
int dp[1 << MAXN];
int dfs(int S) {
    if (sts[0] == S) {
        return 1;  // 边界——可以消灭
    }
    if (dp[S] != -1) {
        return dp[S];
    }
    auto res = 0;
    for (int i = 1; i <= n; i++) {  // 枚举子集~
        if ((S | sts[i]) == S) {
            auto preS = S ^ sts[i];
            res += dfs(preS);
        }
    }
    return dp[S] = res;
}
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int chesse = 1; chesse <= T; chesse++) {  // 我从 0 开始编号机器壬
        cin >> n;
        cin.get();
        for (int i = 0; i <= n; i++) {
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
        auto x = 0;
        for (auto i = 0; i < n; i++) {
            x |= (1 << i);
        }
        cout << dfs(x) << '\n';
    }
    return 0;
}