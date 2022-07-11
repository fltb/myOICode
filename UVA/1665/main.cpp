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
       public:
        unordered_map<Point, Point, hashPoint> fa;
        unordered_set<Point, hashPoint> roots;
        UnionSet() {}
        size_t rootNum() {
            return roots.size();
        }
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
        /**
         * @brief merge u to v (v as father)
         *
         * @param u
         * @param v
         */
        void merge(const Point& u, const Point& v) {
            auto fau = find(u);
            auto fav = find(v);
            fa[fau] = fav;
            inroot(fav);
            if (fav == fau) {
                return;
            }
            outroot(fau);
        }
        Point find(const Point x) {
            if (!fa.count(x) || fa[x] == x) {
                return x;
            } else {
                fa[x] = find(fa[x]);
                return fa[x];
            }
        }
    };

   public:
    Solver(int n_, int m_) : n(n_), m(m_), graph(vector<vector<int>>(n_, vector<int>(m_, 0))) {}
    void readMap(std::istream& is) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                is >> graph[i][j];
            }
        }
    }
    void getAns(std::istream& is, std::ostream& os) {
        int c;
        is >> c;
        vector<int> qs;
        qs.push_back(-1);
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
                while (pos != qs.begin() && *pos >= here) {
                    pos--;
                }
                if (pos != qs.begin()) {
                    here = *pos;
                    rec[*pos].push_back(Point(i, j));
                }
            }
        }
        UnionSet us;
        reverse(qs.begin(), qs.end());
        // 从大到小
        int dirs[2][4] = {
            {1, 0, -1, 0},
            {0, 1, 0, -1}};
        auto valid = [&](const Point& po) {
            return (po.x >= 0 && po.x < n && po.y >= 0 && po.y < m);
        };
        vector<int> ans;
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        for (auto it : qs) {
            if (it == -1) {
                break;
            }
            for (const auto& at : rec[it]) {
                int i = at.x, j = at.y;
                const auto& now = graph[i][j];
                us.merge(at, at);
                for (int k = 0; k < 4; k++) {
                    Point to = Point(i + dirs[0][k], j + dirs[1][k]);
                    const auto& val = graph[to.x][to.y];
                    if (valid(to) && us.fa.count(to) && val >= now) {
                        us.merge(to, at);
                    }
                }
            }
            ans.push_back(us.rootNum());
        }

        std::reverse(ans.begin(), ans.end());
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
        so.readMap(cin);
        so.getAns(cin, cout);
    }
    return 0;
}