#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <tuple>
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
/*
考虑搜索。
使用状压存状态
每次枚举没有并了的两个点生成一个函数，然后看看其他点能不能合并掉。
Over？
*/
const int MAXN = 18, INF = 0x3f3f3f3f;
const double exp = 1e-6;
struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};
inline bool has(int st, int num) {
    return st & (1 << num);
}
inline int disable(int st, int num) {
    return st ^ (1 << num);
}
inline int getBit(int st) {
    int ans = 0;
    while (st) {
        st &= st - 1;
        ans++;
    }
    return ans;
}
inline std::tuple<double, double> genAB(const Point p1, const Point& p2) {
    auto a = (p1.y * p2.x - p2.y * p1.x) / (p1.x * p1.x * p2.x - p2.x * p2.x * p1.x),
         b = (p1.y * p2.x * p2.x - p2.y * p1.x * p1.x) / (p1.x * p2.x * p2.x - p2.x * p1.x * p1.x);
    return std::tuple<double, double>(a, b);
}
inline double func(double a, double b, double x) {
    return a * x * x + b * x;
}
inline bool fkeq(double a, double b) {
    return a + exp > b && a - exp < b;
}
int dp[1 << MAXN], n;
Point ps[MAXN];
/**
 * @brief
 *
 * @param st
 * @return int minimal step to this step from 0
 */
int dfs(int st) {
    auto& dpn = dp[st];
    if (dpn < INF) {
        return dpn;
    }
    if (getBit(st) < 2) {
        return dpn = st > 0;
    }
    for (int i = 0; i < n; i++) {
        if (!has(st, i)) {
            continue;
        }
        auto mergeable = false;
        for (int j = i + 1; j < n; j++) {
            if (i == j || !has(st, j) || fkeq(ps[i].x, ps[j].x)) {
                continue;
            }
            auto ab = genAB(ps[i], ps[j]);
            auto a = std::get<0>(ab),
                 b = std::get<1>(ab);
            if (a >= -exp) {
                continue;
            }
            mergeable = true;
            auto after = disable(disable(st, i), j);
            for (int k = 0; k < n; k++) {
                if (k == i || k == j || !has(st, k) || !fkeq(ps[k].y, func(a, b, ps[k].x))) {
                    continue;
                }
                after = disable(after, k);
            }
            dpn = min(dpn, dfs(after));
        }
        if (!mergeable) {
            auto after = disable(st, i);
            dpn = min(dpn, dfs(after));
        }
    }
    return (dpn != INF ? ++dpn : INF);
}
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int m;
        cin >> ::n >> m;
        for (int i = 0; i < (1 << n); i++) {
            dp[i] = INF;
        }
        auto start = 0;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            ps[i] = Point(x, y);
            start |= (1 << i);
        }
        cout << dfs(start) << '\n';
    }
    return 0;
}