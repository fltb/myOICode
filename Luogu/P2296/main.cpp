#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::vector;

template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
const int INF = 0x3f3f3f3f;
const int MAXN = 10000 + 2;
struct Edge {
    int u, v, c;
    Edge(int from, int to, int cap) : u(from), v(to), c(cap) {}
    int to(int x) { return x == u ? v : u; }
};
int main() {
    std::ios::sync_with_stdio(false);
    int n, m, s, t;
    cin >> n >> m;
    vector<Edge> es;
    vector<vector<int>> orinG;
    vector<vector<int>> oppoG;
    orinG = vector<vector<int>>(n + 2, vector<int>());
    oppoG = vector<vector<int>>(n + 2, vector<int>());
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            continue;
        }
        es.push_back(Edge(u, v, 0));
        orinG[u].push_back(es.size() - 1);
        oppoG[v].push_back(es.size() - 1);
    }

    cin >> s >> t;
    // BFS 反图，判联通性，这样可以避免重边影响
    std::queue<int> q;
    vector<bool> vis(n + 2, false);
    q.push(t);
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        for (auto ei : oppoG[now]) {
            auto& ed = es[ei];
            if (!ed.c) {
                ed.c = 1;
                auto to = ed.to(now);
                if (!vis[to]) {
                    vis[to] = true;
                    q.push(to);
                }
            }
        }
    }
    // 现在可以正图了
    vis = vector<bool> (n + 2, false);
    vis[s] = true;
    std::queue<std::pair<int, int>> qq;
    qq.push(std::make_pair(s, 0));
    while (!qq.empty()) {
        auto now = qq.front().first;
        auto d = qq.front().second;
        qq.pop();
        bool is = true;
        for (auto ei : orinG[now]) {
            auto& ed = es[ei];
            if (!ed.c) {
                is = false;
                break;
            }
        }
        if (is) {
            for (auto ei : orinG[now]) {
                auto& ed = es[ei];
                auto to = ed.to(now);
                if (!vis[to]) {
                    if (to == t) {
                        cout << d + 1 << '\n';
                        return 0;
                    }
                    vis[to] = true;
                    qq.push(std::make_pair(to, d + 1));
                }
            }
        }
    }
    cout << -1 << '\n';
    return 0;
}