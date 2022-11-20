#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>
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
const int MOD = 998244353;
const int MAXD = 1e6 + 2;
long long dp[MAXD];
bool a[MAXD];
void init() {
    dp[1] = 1;
    for (int i = 2; i < MAXD; i++) {
        dp[i] = (dp[i - 1] + 1) * (dp[i - 1] + 1) % MOD;
    }
}
int dep;
long long dfs(int d) {
    if (d >=dep) {
        return 1;
    }
    if (!a[d]) {
        return (dfs(d + 1)+1) * (dp[dep - d - 1]+1) % MOD;
    } else {
        return (dfs(d + 1)+1) * (dp[dep - d]+1) % MOD;
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    init();
    int T;
    cin >> T;
    while (T--) {
        cin >> dep;
        cin.get();
        std::string st;
        cin >> st;
        int lst1 = 0;
        for (int i = 1; i < st.length(); i++) {
            a[i] = st[i] - '0';
            if (a[i] == 1) {
                lst1 = i;
            }
        }
        a[lst1] = 0;
        lst1++;
        while (lst1 < st.length()) {
            a[lst1] = 1;
            lst1++;
        }
        cout << dfs(1) << '\n';
    }
    return 0;
}