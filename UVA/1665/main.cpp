#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::cin;
using std::cout;
using std::lower_bound;
using std::unordered_map;
using std::unordered_set;
using std::vector;
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
const int INF = 0x7ffffff;
const int MAXN = 1000 + 2;
class Solver {
    vector<vector<int>> graph;
    int n, m;
    struct Point {
        int x, y;
        Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
        bool operator==(const Point& another) const {
            return x == another.x && y == another.y;
        }
    };
    struct hashPoint {
        size_t operator()(const Point& p) const {
            return p.x * MAXN + p.y;
        }
    };

    /**
     * @brief 第一次超时了，加上一个记录点编号的东西，然后按照离散化后的编号不断取出就可以了
     *
     */
    unordered_map<int, vector<Point>> rec;
    class UnionSet {
        unordered_map<Point, Point, hashPoint> fa;
        unordered_set<Point, hashPoint> roots;
        int cnt;
        void inroot(const Point& x) {
            if (!roots.count(x)) {
                roots.insert(x);
            }
        }
        void outroot(const Point& x) {
            if (roots.count(x)) {
                roots.erase(x);
            }
        }

       public:
        UnionSet() : cnt(0) {}
        size_t rootNum() {
            return roots.size();
        }
        void insert(const Point& x) {
            fa[x] = x;
            inroot(x);
            cnt++;
        }
        /**
         * @brief merge u to v (v as father)
         *
         * @param u
         * @param v
         */
        void merge(const Point& u, const Point& v) {
            auto fau = find(u);
            auto fav = find(v);
            if (fav == fau) {
                return;
            }
            fa[fau] = fav;
            outroot(fau);
            cnt--;
        }

        Point find(const Point x) {
            if (fa[x] == x) {
                return x;
            } else {
                return fa[x] = find(fa[x]);
            }
        }

        bool contain(const Point& x) {
            return fa.count(x);
        }
    };

   public:
    Solver(int n_, int m_) : n(n_), m(m_), graph(vector<vector<int>>(n_, vector<int>(m_, 0))) {}
    void getAns(std::istream& is, std::ostream& os) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                is >> graph[i][j];
            }
        }

        int c;
        is >> c;
        vector<int> qs;
        for (int i = 0; i < c; i++) {
            int t;
            cin >> t;
            qs.push_back(t);
        }

        // 离散化
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                auto& here = graph[i][j];
                auto pos = lower_bound(qs.begin(), qs.end(), here);
                if (pos != qs.begin()) {
                    here = *(--pos);
                    rec[*pos].push_back(Point(i, j));
                }
            }
        }

        const int dirs[2][4] = {
            {1, 0, -1, 0},
            {0, 1, 0, -1}};
        auto valid = [&](const Point& po) {
            return (po.x >= 0 && po.x < n && po.y >= 0 && po.y < m);
        };
        auto getVal = [&](const Point& x) {
            return graph[x.x][x.y];
        };
        auto walk = [&dirs](const Point& x, int s) {
            return Point(x.x + dirs[0][s], x.y + dirs[1][s]);
        };

        // 从大到小
        UnionSet us;
        reverse(qs.begin(), qs.end());
        vector<int> ans;
        for (auto it : qs) {
            for (const auto& at : rec[it]) {
                us.insert(at);
                for (int k = 0; k < 4; k++) {
                    Point to = walk(at, k);
                    if (valid(to) && us.contain(to)) {
                        us.merge(at, to);
                    }
                }
            }
            ans.push_back(us.rootNum());
        }

        reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++) {
            os << ans[i] << ((i + 1 == ans.size()) ? '\n' : ' ');
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
#ifdef FLOATINGBLOCKS
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        Solver so(n, m);
        so.getAns(cin, cout);
    }
    return 0;
}