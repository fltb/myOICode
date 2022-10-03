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
// 当前节点编号，所有子树当中先前已经无了几个 = 当前状态最小代价
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
    // 当时我就不炸了
    dp[x][0] = 0;
    for (auto to : tree[x]) {
        if (to != fa) {
            dfs(to, x);
        }
    }
    // 来吧，背包！
    int ss = 0;
    for (auto to : tree[x]) {
        if (to != fa) {
            ss += sz[x];
            // j 是当前节点的所有子树爆炸了的节点个数
            for (int j = ss - 1; j > 0; j--) {
                for (int i = max(j - ss + sz[to], 1); i <= min(sz[to] - 1, j); i++) {
                    if (dp[to][i] != -1 && dp[x][j - i] != -1) {  // 在先前的爆炸的基础上面 假如先前有可以达到 j 状态的方法
                        // 从 j - i 转到 j 所需要的代价
                        auto tVal = dp[x][j - i] + dp[to][i];
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
    // 收个尾，我原地爆炸~
    dp[x][sz[x] - 1] = f[sz[x]];
    for (int i = 0; i < sz[x] - 1; i++) {
        if (dp[x][i] == -1) {
            continue;
        }
        auto v = dp[x][i] + f[sz[x] - i];
        dp[x][sz[x] - 1] = min(dp[x][sz[x] - 1], v);
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
    f[1] = 0;
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

    cout << dp[1][sz[1] - 1] << '\n';
    return 0;
}