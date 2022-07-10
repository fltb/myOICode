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
using std::hash;
using std::lower_bound;
using std::unordered_map;
using std::unordered_set;
using std::vector;
template <typename T>
inline T max(T a, T b)
{
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b)
{
    return a < b ? a : b;
}
const int INF = 0x7ffffff;
class Solver
{
    vector<vector<int>> graph;
    int n, m;
    struct Point
    {
        int x, y;
        Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    };
    struct hashPoint
    {
        size_t operator()(const Point& p) const
        {
            auto hash1 = hash<int>{}(p.x);
            auto hash2 = hash<int>{}(p.y);

            if (hash1 != hash2)
            {
                return hash1 ^ hash2;
            }

            return hash1;
        }
    };
    class UnionSet
    {
        unordered_map<Point, Point, hashPoint> fa;
        unordered_set<Point, Point, hashPoint> roots;

       public:
        UnionSet() {}
        size_t rootNum()
        {
            return roots.size();
        }
        void inroot(const Point& x)
        {
            if (!roots.count(x))
            {
                roots.insert(x);
            }
        }
        /**
         * @brief merge u to v (v as father)
         *
         * @param u
         * @param v
         */
        void merge(const Point& u, const Point& v)
        {
            fa[u] = v;
            if (!fa.count(v))
            {
                inroot(v);
            }
            if (roots.count(u))
            {
                roots.erase(u);
            }
        }
        Point find(const Point& x)
        {
            if (!fa.count(x))
            {
                return x;
            }
            else
            {
                return fa[x] = find(fa[x]);
            }
        }
    };

   public:
    Solver(int n_, int m_) : n(n_), m(m_), graph(vector<vector<int>>(n_, vector<int>(m_, 0))) {}
    void readMap(std::istream& is)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                is >> graph[i][j];
            }
        }
    }
    void getAns(std::istream& is, std::ostream& os)
    {
        int c;
        is >> c;
        vector<int> qs;
        for (int i = 0; i < c; i++)
        {
            int t;
            cin >> t;
            qs.push_back(t);
        }
        // 离散化
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                auto& here = graph[i][j];
                auto pos = lower_bound(qs.begin(), qs.end(), here);
                if (pos != qs.begin())
                {
                    if (*pos > here)
                    {
                        pos--;
                    }
                    here = *pos;
                }
            }
        }
        UnionSet us;
        reverse(qs.begin(), qs.end());
        // 从大到小
        int dirs[2][4] = {
            {1, 0, -1, 0},
            {0, 1, 0, -1}};
        auto valid = [&](const Point& po)
        {
            return (po.x >= 0 && po.x < n && po.y >= 0 && po.y < m);
        };
        vector<int> ans;
        for (auto it : qs)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    const auto& now = graph[i][j];
                    if (now >= it)
                    {
                        auto at = Point(i, j);
                        us.inroot(at);
                        for (int k = 0; k < 4; k++)
                        {
                            Point to = Point(i + dirs[0][k], j + dirs[1][k]);
                            if (valid(to))
                            {
                                const auto& val = graph[to.x][to.y];
                                if (val >= now)
                                {
                                    us.merge(at, to);
                                }
                            }
                        }
                    }
                }
            }
            ans.push_back(us.rootNum());
        }
        std::reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++)
        {
            os << ans[i] << ((i + 1 == ans.size()) ? ' ' : '\n');
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        Solver so(n, m);
        so.readMap(cin);
        so.getAns(cin, cout);
    }
    return 0;
}