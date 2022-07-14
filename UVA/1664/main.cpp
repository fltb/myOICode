#include <algorithm>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
const int MAXN = 200000 + 2;
/**
 * @brief fa 父节点 w 权值 c 当前树大小
 *
 */
int fa[MAXN], c[MAXN];
long long w[MAXN];

struct Edge {
    int u, v;
    long long c;
    Edge(int u_ = 0, int v_ = 0, long long c_ = 0) : u(u_), v(v_), c(c_) {}
    bool operator<(const Edge& e) const {
        return c < e.c;
    }
};

Edge edges[MAXN];

/**
 * @brief 一个贪心的方法，有点类似最小生成树
 *
 */
int main() {
    std::ios::sync_with_stdio(false);
    int n;

    while (cin >> n) {
        /**
         * @brief en is num of edges(1 miner than n)
         * 
         */
        const int en = n - 1;

        for (int i = 0; i <= n; i++) {
            fa[i] = i;
            c[i] = 1;
            w[i] = 0;
        }

        for (int i = 0; i < en; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            edges[i] = Edge(u, v, c);
        }
        std::sort(edges, edges + en, [](const Edge& e1, const Edge& e2) {
            return e2 < e1;
        });

        std::function<int(int)> find = [&find](int x) {
            return fa[x] == x ? x : fa[x] = find(fa[x]);
        };

        auto mergeVal = [](int u, int v, long long cap) {
            return w[v] + c[u] * cap;
        };
        /** @brief merge u to v *edge capacity(c)*/
        auto merge = [&mergeVal](int u, int v, long long cap) {
            fa[u] = v;
            c[v] += c[u];
            w[v] = mergeVal(u, v, cap);
        };

        for (int i = 0; i < en; i++) {
            const auto& e = edges[i];
            auto u = find(e.u), v = find(e.v);
            if (mergeVal(v, u, e.c) > mergeVal(u, v, e.c)) {
                merge(v, u, e.c);
            } else {
                merge(u, v, e.c);
            }
        }

        cout << w[find(1)] << '\n';
    }
    return 0;
}