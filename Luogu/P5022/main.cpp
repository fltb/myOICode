#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <streambuf>
#include <vector>
using std::cin;
using std::cout;
const int MAXN = 5000 + 5;
struct Edge {
    int u, v;
    bool enable;
    Edge(int u_ = 0, int v_ = 0) : u(u_), v(v_), enable(true) {}
    int to(int x) {
        return enable ? (x == u ? v : u) : -1;
    }
};
int n, m;
std::vector<Edge> es;
std::vector<int> g[MAXN];
namespace dfs1 {
bool vis[MAXN];
void dfs1(int u) {
    vis[u] = true;
    cout << u << ' ';
    for (auto e : g[u]) {
        auto v = es[e].to(u);
        if (!vis[v]) {
            dfs1(v);
        }
    }
}
}  // namespace dfs1

namespace dfs2 {
int ans[MAXN], rec[MAXN], vis[MAXN], cnt, miner, flag;
void init() {
    for (int i = 1; i <= n; i++) {
        ans[i] = n + 1;
    }
    vis[0] = true;
}
void nxtRound() {
    if (miner && cnt == n) {
        for (int i = 1; i <= n; i++) {
            ans[i] = rec[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        vis[i] = false;
        rec[i] = 0;
    }
    flag = miner = cnt = 0;
}
void dfs2(int u) {
    if (flag) {
        return;
    }
    ++cnt;
    if (!miner) {
        if (ans[cnt] < u) {  // 字~典~序~
            flag = true;
            return;
        } else if (ans[cnt] > u) {
            miner = true;
        }
    }
    rec[cnt] = u;
    vis[u] = 1;
    for (auto e : g[u]) {
        auto v = es[e].to(u);
        if (v != -1 && !vis[v]) {
            dfs2(v);
        }
    }
}
void ptAns() {
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
}
}  // namespace dfs2
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        es.push_back(Edge(u, v));
        int eid = es.size() - 1;
        g[u].push_back(eid);
        g[v].push_back(eid);
    }
    for (int i = 1; i <= n; i++) {
        std::sort(g[i].begin(), g[i].end(), std::function<bool(int, int)>([i](int x, int y) {
            return es[x].to(i) < es[y].to(i);
        }));
    }
    if (m == n - 1) {
        dfs1::dfs1(1);
    } else {
        dfs2::init();
        for (auto i = 0; i < es.size(); i++) {
            if (i > 0) {
                es[i - 1].enable = true;
            }
            es[i].enable = false;
            dfs2::nxtRound();
            dfs2::dfs2(1);
        }
        dfs2::nxtRound();
        dfs2::ptAns();
    }
    cout << '\n';
}