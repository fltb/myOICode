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
void chroot(int x) {
    /*int p = fa[x];
    int q = x;
    while (p != fa[p]) {
        int t = q;
        q = p;
        p = fa[p];
        act.push_back(std::make_tuple(q, fa[q]));
        fa[q] = t;
    }
    act.push_back(std::make_tuple(p, fa[p]));
    fa[p] = q;*/
    if (x != fa[x]) {
        chroot(fa[x]);
    }
    act.push_back(std::make_tuple(fa[x], fa[fa[x]]));
    act.push_back(std::make_tuple(x, fa[x]));
    fa[x] = fa[fa[x]] = x;
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
    for (int i=act.size()-1;i>=0;i--) {
        fa[std::get<0>(act[i])] = std::get<1>(act[i]);
    }
    act.clear();
}

// union find
int f[1050];
void INIT(int size) {
    for (int i = 0; i <= size; i++) f[i] = i;
}

int findf(int x) {
    while (f[x] != x) x = f[x];
    return x;
}

void setroot(int x) {
    if (f[x] != x)
        setroot(f[x]);
    f[x] = f[f[x]] = x;
}

void link(int a, int b) {
    setroot(a);
    f[a] = b;
}

void cut(int a, int b) {
    setroot(a);
    f[b] = b;
}
int main() {
#ifdef FLOATINGBLOCKS
    freopen("secret.in", "r", stdin);
    freopen("secret.oo", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < MAXN; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        es[i] = Edge(u, v, c);
    }
    std::sort(&es[1], &es[m + 1]);
    int inEs = 0;
    long long all = 0, ans = 0;
    std::vector<int> avail;
    for (int cnt = 1; cnt <= m; cnt++) {
        auto& e = es[cnt];
        auto u = find(e.u), v = find(e.v);
        if (u != v) {
            // merge(u, v);
            inEs++;
            all += e.c;
            merge(e.u, e.v);
            g[u].push_back(cnt);
            g[v].push_back(cnt);
            if (inEs == n - 1) {
                for (int i = cnt + 1; i <= m; i++) {
                    avail.push_back(i);
                }
                break;
            }
        } else {
            avail.push_back(cnt);
        }
    }
#ifdef FLOATINGBLOCKS
    for (int i = 1; i <= n; i++) {
        for (auto ei : g[i]) {
            auto e = es[ei];
            auto u = find(e.u), v = find(e.v);
            if (u != v) {
                throw "err";
            }
        }
    }
#endif
    for (int i = 1; i <= n; i++) {
        split(i);
        int ansAdd = all;
        for (auto ei : g[i]) {
            ansAdd -= es[ei].c;
        }
        if (g[i].size() == 1) {
            ans += ansAdd;
            continue;
        }
        int inEs = n - 1 - g[i].size();
        for (int add : avail) {
            auto& e = es[add];
            if (e.u == i || e.v == i) {
                continue;
            }
            auto u = find(e.u), v = find(e.v);
            if (u != v) {
                ansAdd += e.c;
                merge(e.u, e.v);
                inEs++;
            }
            if (inEs == n - 2) {
                break;
            }
        }
        if (inEs == n - 2) {
            ans += ansAdd;
        } else {
            ans--;
        }
        restore();
#ifdef FLOATINGBLOCKS
        for (int i = 1; i <= n; i++) {
            for (auto ei : g[i]) {
                auto e = es[ei];
                auto u = find(e.u), v = find(e.v);
                if (u != v) {
                    throw "err";
                }
            }
        }
#endif
    }
    cout << ans << '\n';
    return 0;
}