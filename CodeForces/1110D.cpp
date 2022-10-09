#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <functional>
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
const int LEN = 3, MODE = 2;
int arr[2]{-1, -1};  // 顺手滚动数组
int dp[2][LEN][MODE];
const std::function<bool(int, int)> methods[] = {
    [](int a, int b) {  // solid
        return a == b;
    },
    [](int a, int b) {  // liner
        return a == b + 1;
    }};
bool valid(int mode, int i) {
    return methods[mode](arr[i & 1], arr[(i + 1) & 1]);
}
void update(int& a, int b) {
    a = max(a, b);
}
int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int idx = 1; idx < LEN; idx++) {
        for (int mode = 0; mode < MODE; mode++) {
            dp[0][idx][mode] = -1;  // disable these situation
        }
    }
    for (int cur = 1; cur <= n; cur++) {
        auto now = cur & 1, pre = (cur + 1) & 1;
        cin >> arr[now];
        int mx = 0;
        for (int idx = 0; idx < LEN; idx++) {
            for (int md = 0; md < MODE; md++) {
                update(mx, dp[pre][idx][md]);
            }
        }
        for (int md = 0; md < MODE; md++) {
            dp[now][0][md] = mx;
        }
        for (int idx = 1; idx < LEN; idx++) {
            for (int md = 0; md < MODE; md++) {
                dp[now][idx][md] = -1;
                if (valid(md, now)) {
                    update(dp[now][idx][md], dp[pre][idx - 1][md]);
                }
            }
        }
        for (int md = 0; md < MODE; md++) {
            if (dp[now][LEN - 1][md] != -1) {
                dp[now][LEN - 1][md]++;
            }
        }
    }
    auto ans = 0;
    for (int idx = 0; idx < LEN; idx++) {
        for (int md = 0; md < MODE; md++) {
            update(ans, dp[n & 1][idx][md]);
        }
    }
    cout << ans << '\n';
    return 0;
}