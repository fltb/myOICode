#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::vector;
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
经典 chroot
*/
struct Edge {
    int u, v, c;
    Edge(int a, int b, int d) : u(a), v(b), c(d) {}
    int to(int x) { return u == x ? v : u; }
};
const int MAXN = 100000 + 2;
vector<Edge> es;
vector<int> g[MAXN];
int point[MAXN];
int sz[MAXN];
long long sum[MAXN];
int total;
void dfs(int x, int fa) {
    sz[x] = point[x];
    for (auto ei : g[x]) {
        auto to = es[ei].to(x);
        if (to != fa) {
            dfs(to, x);
            sum[x] += sum[to] + (long long)es[ei].c * sz[to];
            sz[x] += sz[to];
        }
    }
}
long long dp[MAXN], ans = 0x3f3f3f3f3f3f3f3f;
void chroot(int x, int fa, int fae) {
    // 当前的根 之前的根
    // 草稿不好打，算了
    // dp[x] = dp[fa] + es[fae].c * (n - sz[x]) - es[fae].c * sz[x];
    dp[x] = dp[fa] + (long long)es[fae].c * (total - 2 * sz[x]);
    ans = min(ans, dp[x]);
    for (auto ei : g[x]) {
        auto to = es[ei].to(x);
        if (to != fa) {
            chroot(to, x, ei);
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> point[i];
        total += point[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        es.push_back(Edge(u, v, c));
        g[u].push_back(es.size() - 1);
        g[v].push_back(es.size() - 1);
    }
    dfs(1, -1);
    dp[1] = sum[1];
    for (auto ei : g[1]) {
        chroot(es[ei].to(1), 1, ei);
    }
    cout << ans << '\n';    
    return 0;
}