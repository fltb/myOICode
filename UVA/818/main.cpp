#include <algorithm>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <type_traits>
#include <vector>
#define cosnt const
using std::cin;
using std::cout;
using std::function;
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
const int MAXN = 15 + 2;
int graph[MAXN][MAXN], vis[MAXN];

inline int cntBit(int x) {
    int cnt = 0;
    while (x) {
        x &= x - 1;
        cnt++;
    }
    return cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n, sets = 1;
    while (cin >> n && n) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                graph[i][j] = 0;
            }
        }
        int u, v;
        while (cin >> u >> v && u != -1 && v != -1) {
            graph[u][v] = graph[v][u] = 1;
        }
        int ans = n - 1;
        // 一个二进制的枚举，枚举当前已经合并起来了的变量
        for (int i = 0; i < (1 << n); i++) {
            auto s = i << 1;  // 编号从 1 开始
            auto inS = [&s](int j) {
                return s & (1 << j);
            };
            for (int i = 0; i <= n; i++) {
                vis[i] = 0;
            }
            auto two = [&s, &n, &inS]() {
                for (int i = 1; i <= n; i++) {
                    if (!inS(i)) {
                        int cnt = 0;
                        for (int j = 1; j <= n; j++) {
                            if (!inS(j) && graph[i][j]) {
                                cnt++;
                            }
                        }
                        if (cnt > 2) {
                            return false;
                        }
                    }
                }
                return true;
            };
            // 尝试给每个没有合并的变量进行统计
            std::function<bool(int, int)> dfsCir = [&s, &n, &inS, &dfsCir](int x, int fa) {
                // 看看从当前编号开始的点会不会形成环
                bool ok = true;
                vis[x] = true;
                for (int i = 1; i <= n; i++) {
                    if (!inS(i) && graph[x][i] && i != fa) {
                        if (vis[i]) {
                            return false;
                        }
                        ok = dfsCir(i, x);
                    }
                }
                return ok;
            };
            int rest = 0;
            // 是堆链
            auto check = [&inS, &dfsCir, &n, &rest]() {
                for (int j = 1; j <= n; j++) {
                    if (!inS(j) && !vis[j]) {
                        if (dfsCir(j, -1)) {
                            rest++;
                        } else {
                            return false;
                        }
                    }
                }
                return true;
            };
            auto deleted = cntBit(s);
            // 可以合并掉
            if (two() && check() && deleted + 1 >= rest) {
                ans = min(ans, deleted);
            }
        }
        cout << "Set " << sets++ << ": Minimum links to open is " << ans << "\n";
    }
    return 0;
}
