#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <istream>
#include <vector>
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
typedef long long ll;
const int MAXN = 5000 + 5;
const ll INF = 0x00033fffffffffff;
ll f[MAXN];
int n, sz[MAXN];
std::vector<int> tree[MAXN];
// 所有子树被清空时： 当前节点，子树当中先前已经无了的 = 当前状态最小代价
ll dp[MAXN][MAXN];
int dfsZ(int x, int fa) {
    sz[x] = 1;
    for (auto to : tree[x]) {
        if (to != fa) {
            sz[x] += dfsZ(to, x);
        }
    }
    for (int i = 0; i <= sz[x]; i++) {
        dp[x][i] = -1;
    }
    return sz[x];
}

void dfs(int x, int fa) {
    for (auto to : tree[x]) {
        if (to != fa) {
            dfs(to, x);
        }
    }
    // 原地爆炸
    dp[x][0] = f[sz[x]];
    // 来吧，背包！
    for (auto to : tree[x]) {
        if (to != fa) {
            for (int i = 0; i < sz[to]; i++) {
                if (dp[to][i] != -1) {    // 在先前的爆炸的基础上面
                    auto s = sz[to] - 1;  // 先前爆炸掉了的个数
                    // j 是当前节点子树爆炸了的个数
                    for (int j = sz[x] - 1; j - s >= 0; j--) {
                        //  假如先前有可以达到 j - s 状态的方法
                        if (dp[x][j - s] != -1) {
                            // 从 j - s 转到 j 所需要的代价
                            auto tVal = dp[x][j - s] - f[sz[x] - (j - s)] + dp[to][i] + f[sz[x] - j];
                            if (dp[x][j] == -1) {
                                dp[x][j] = tVal;
                            } else {
                                dp[x][j] = min(dp[x][j], tVal);
                            }
                        }
                    }
                }
            }
        }
    }
#ifdef FLOATINGBLOCK
    cout << "At " << x << " :\n";
    for (int i = 0; i < sz[x]; i++) {
        cout << i << '\t';
    }
    cout << '\n';
    for (int i = 0; i < sz[x]; i++) {
        cout << dp[x][i] << '\t';
    }
    cout << std::endl;
#endif
}
int main() {
    std::ios::sync_with_stdio(false);
#ifdef FLOATINGBLOCKS
    freopen("T2ex2.in", "r", stdin);
#endif
    cin >> n;
    f[1] = -1;
    f[n] = -1;
    for (int i = 2; i <= n; i++) {
        cin >> f[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfsZ(1, -1);
    dfs(1, -1);
    ll ans = INF;
    for (int i = 0; i < sz[1]; i++) {
        if (dp[1][i] != -1) {
            ans = min(ans, dp[1][i]);
        }
    }
    cout << ans << '\n';
    return 0;
}