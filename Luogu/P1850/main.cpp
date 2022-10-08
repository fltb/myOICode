#include <algorithm>
#include <cstdio>
#include <iomanip>
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
const int MAXV = 300 + 5, MAXN = 2000 + 5, INF = 0x3f3f3f3f;
const double INFD = 1e17 + 2;
int f[MAXV][MAXV];
int c[MAXN], d[MAXN];
double k[MAXN];
/*
如果我要得到图上路径的总权和，我就先跑一遍 Floyd 两两最短路。看数据应该是正解。

然后，我们开始枚举。
对于一个节点 c 可以变成 e 前 a 后 b，有换和不换两种选择。令当前节点为 b （c 的后继）
    不换： dis(a,c)+dis(c, b)
    换： (dis(a,c)+dis(c,b))*(1-p) + (dis(a,d)+dis(d,b))*p
好像可以 dp ？来吧！
    状态: [当前第几节][到当前的时候换掉了几节][当前在哪里] = 总共的期望
    转移：
        边界：dp[1][0][0], dp[1][1][1]
        过程：
            不换: dp[i][j][0] = min(dp[i][j][0]+Dis,
                                    dp[j][j][1] + Dis换*p + Dis不换*(1-p))
            换   dp[i][j][1] = min( dp[i][j-1][0]+ Disp(1-p),
                                    dp[i][j-1][1] + Dis 00 01 10 11)
    Over? Over!
*/
double dp[MAXN][MAXN][2];
int main() {
    std::ios::sync_with_stdio(false);
    int n, m, v, e;
    cin >> n >> m >> v >> e;
    for (int i = 0; i <= v; i++) {
        for (int j = 0; j <= v; j++) {
            f[i][j] = INF;
        }
    }
    // ERR 这里小心初始化，自己和自己或者从前面转移过来是 0 ！！！
    for (int i = 1; i <= v; i++) {
        f[i][i] = 0;
    }
    // ERR 初始化 ...
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j][0] = dp[i][j][1] = INFD;
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }
    for (int i = 0; i < e; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        f[u][v] = f[v][u] = min(f[u][v], c);
    }
    // ERR 把这个 v 当成 n 了
    for (int k = 1; k <= v; k++) {
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    dp[1][0][0] = dp[1][1][1] = 0.0;
    for (int i = 2; i <= n; i++) {
        dp[i][0][0] = dp[i - 1][0][0] + f[c[i - 1]][c[i]];
        for (int j = 1; j <= min(m, i); j++) {
            auto nowC = c[i], nowD = d[i], preC = c[i - 1], preD = d[i - 1];
            auto nowK = k[i], preK = k[i - 1];
            dp[i][j][0] = min(
                dp[i - 1][j][0] + f[preC][nowC],
                dp[i - 1][j][1] + f[preD][nowC] * preK + f[preC][nowC] * (1 - preK));
            dp[i][j][1] = min(
                dp[i - 1][j - 1][0] + f[preC][nowD] * nowK + f[preC][nowC] * (1 - nowK),
                dp[i - 1][j - 1][1] +
                    f[preC][nowC] * (1 - preK) * (1 - nowK) +
                    f[preD][nowC] * preK * (1 - nowK) +
                    // ERR f[preC][nowD] * (>>>>>>>>>>>>>>i<<<<<<<<<<<<<< - preK) * nowK +
                    f[preC][nowD] * (1 - preK) * nowK +
                    f[preD][nowD] * preK * nowK);
        }
    }
    double ans = INFD;
    for (int i = 0; i <= m; i++) {
        for (int k = 0; k <= min(1, m); k++) {
            ans = min(ans, dp[n][i][k]);
        }
    }
    cout << std::setprecision(2) << std::setiosflags(std::ios::fixed) << ans << '\n';
    return 0;
}