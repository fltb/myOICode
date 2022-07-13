#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <stack>
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
struct Edge {
    int u, v, c;
    Edge(int u_ = 0, int v_ = 0, int c_ = 0) : u(u_), v(v_), c(c_) {}
    int to(int x) {
        return x == u ? v : u;
    }
};
class Solver {
    int n;
    vector<Edge> edges;
   public:
    Solver(int n_) : n(n_) {}
    void rd(int t) {
        vector<int> cnt(n + 2, 0);
        vector<int> mxcnt(n + 2, 0);
        for (int i = 0; i < n - 1; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            edges.push_back(Edge(u, v, c));
            cnt[u] += c;
            cnt[v] += c;
            mxcnt[u] = max(mxcnt[u], c);
            mxcnt[v] = max(mxcnt[v], c);
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            const auto mx = mxcnt[i], c = cnt[i];
            if (mx > c - mx) {
                ans += mx * 2 - c;
            } else if (c % 2) {
                ans++;
            }
        }

        cout << "Case #" << t << ": " << ans/2 << '\n';
        return;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        Solver so(n);
        so.rd(i);
    }
    return 0;
}