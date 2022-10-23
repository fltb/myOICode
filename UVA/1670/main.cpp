#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <tuple>
#include <vector>
#define cosnt const
using std::cin;
using std::cout;
using std::function;
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

int main() {
    std::ios::sync_with_stdio(false);
    // freopen("kingdom.in", "r", stdin);
    // freopen("kingdom.in", "w", stdout);
    int n;
    while (cin >> n) {
        vector<vector<int>> g(n + 1, vector<int>());
        int start = -1;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            if (g[u].size() > 1) {
                start = u;
            }
            if (g[v].size() > 1) {
                start = v;
            }
        }
        vector<int> rec;
        vector<std::tuple<int, int>> ans;
        function<void(int, int)> dfs = [&dfs, &n, &g, &rec, &ans](int now, int fa) {
            bool leaf = true;
            for (auto to : g[now]) {
                if (to != fa) {
                    dfs(to, now);
                    leaf = false;
                }
            }
            if (leaf) {
                rec.push_back(now);
            }
            if (rec.size() == 3) {
                ans.push_back(std::make_tuple(rec[0], rec[2]));
                auto tmp = rec[1];
                rec.clear();
                rec.push_back(tmp);
            }
        };
        dfs(start, -1);
        if (rec.size() == 2) {
            ans.push_back(std::make_tuple(rec[0], rec[1]));
        } else if (rec.size() == 1) {
            ans.push_back(std::make_tuple(start, rec[0]));
        }
        cout << ans.size() << '\n';
        for (auto a : ans) {
            cout << std::get<0>(a) << ' ' << std::get<1>(a) << '\n';
        }
#ifdef FLOATINGBLOCKS
        cout << std::endl;
#endif
    }
    return 0;
}