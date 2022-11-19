#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <ios>
#include <iostream>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>
#define cosnt const
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
const int MAXN = 300005 + 2;
struct Edge {
    int u, v, c;
    Edge(int uu = 0, int vv = 0, int cc = 0) : u(uu), v(vv), c(cc) {}
    int to(int x) {
        return x == u ? v : u;
    }
    bool operator<(const Edge& x) {
        return c == x.c ? (u == x.u ? v < x.v
                                    : u < x.u)
                        : c < x.c;
    }
};
struct COMMON_US {
    int fa[MAXN];
    COMMON_US() {
        for (int i = 1; i < MAXN; i++) {
            fa[i] = i;
        }
    }
    int find(int x) {
        return fa[x] == x ? x : x = find(fa[x]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        fa[u] = v;
    }
} us;
int fa[MAXN];
Edge es[MAXN * 2];
std::vector<int> g[MAXN];
std::vector<std::tuple<int, int>> act;

inline int find(int x) {
    while (x != fa[x]) {
        x = fa[x];
    }
    return x;
}
inline void chroot(int x) {
    int p = fa[x];
    int q = x;
    while (p != fa[p]) {
        int t = q;
        q = p;
        p = fa[p];
        act.push_back(std::make_tuple(q, fa[q]));
        fa[q] = t;
    }
    act.push_back(std::make_tuple(p, fa[p]));
    fa[p] = q;
}
inline void merge(int u, int v) {
    chroot(v);
    act.push_back(std::make_tuple(v, fa[v]));
    fa[v] = u;
}
inline void split(int x) {
    act.clear();
    for (auto ei : g[x]) {
        auto& e = es[ei];
        auto to = e.to(x);
        if (fa[to] == x) {
            act.push_back(std::make_tuple(to, fa[to]));
            fa[to] = to;
        }
    }
    act.push_back(std::make_tuple(x, fa[x]));
    fa[x] = x;
}
inline void restore() {
    for (auto to : act) {
        fa[std::get<0>(to)] = std::get<1>(to);
    }
    act.clear();
}
int main() {
    
    return 0;
}