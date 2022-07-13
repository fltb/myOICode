#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
using std::lower_bound;
// using std::unordered_set;
using std::vector;
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
template <typename T>
inline void read(T& t) {
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
const int INF = 0x7ffffff;
const int MAXN = 1000 + 2, MAXC = 1e5 + 2;
struct Point {
    int x, y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    bool operator==(const Point& another) const {
        return x == another.x && y == another.y;
    }
};

/**
 * @brief 把哈希表去掉算了
 *
 */
int fa[MAXN * MAXN + 2];
class UnionSet {
    int cnt;
    void inroot() {
        cnt++;
    }
    void outroot() {
        cnt--;
    }

    int pointToN(const Point& po) {
        return po.x * MAXN + po.y;
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

   public:
    UnionSet(int n) : cnt(0) {
        for (int i = 0; i < (n + 1) * (n + 1) + 2; i++) {
            fa[i] = -1;
        }
    }
    size_t rootNum() {
        return cnt;
    }
    void insert(const Point& x) {
        fa[pointToN(x)] = pointToN(x);
        inroot();
    }
    /**
     * @brief merge u to v (v as father)
     *
     * @param u
     * @param v
     */
    void merge(const Point& u, const Point& v) {
        auto fau = find(pointToN(u));
        auto fav = find(pointToN(v));
        if (fav == fau) {
            return;
        }
        fa[fau] = fav;
        outroot();
    }

    bool contain(const Point& x) {
        return fa[pointToN(x)] != -1;
    }
};

int hs[MAXN][MAXN];
Point graph[MAXN * MAXN];
int cg;
int qs[MAXC],
    ans[MAXC];

class Solver {
    int n, m;
    const int dirs[2][4] = {
        {1, 0, -1, 0},
        {0, 1, 0, -1}};
    bool valid(const Point& po) {
        return (po.x >= 0 && po.x < n && po.y >= 0 && po.y < m);
    }
    int getVal(const Point& x) {
        return hs[x.x][x.y];
    }
    Point walk(const Point& x, int s) {
        return Point(x.x + dirs[0][s], x.y + dirs[1][s]);
    }

   public:
    Solver(int n_, int m_) : n(n_), m(m_) {
        cg = 0;
    }

    void getAns() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                read(hs[i][j]);
                graph[cg++] = Point(i, j);
            }
        }
        std::sort(graph, graph + cg, [](const Point& g1, const Point& g2) {
            return hs[g1.x][g1.y] > hs[g2.x][g2.y];
        });
        int c;
        read(c);
        for (int i = 0; i < c; i++) {
            read(qs[i]);
        }

        // 从大到小
        UnionSet us(n);
        int i = c - 1, j = 0;
        while (i > 0) {
            while (j < cg) {
                const auto& at = graph[j];
                while (getVal(at) <= qs[i]) {
                    ans[i] = us.rootNum();
                    i--;
                }
                us.insert(at);
                for (int k = 0; k < 4; k++) {
                    Point to = walk(at, k);
                    if (valid(to) && us.contain(to)) {
                        us.merge(at, to);
                    }
                }
                j++;
            }
        }

        for (int i = 0; i < c; i++) {
            std::printf("%d ", ans[i]);
        }
        std::putchar('\n');
    }
};

int main() {
#ifdef FLOATINGBLOCKS
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n), read(m);
        Solver so(n, m);
        so.getAns();
    }
    return 0;
}