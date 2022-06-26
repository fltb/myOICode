#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <iostream>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::sqrt;
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
const int MAXN = 100 + 5;
const double INF = 0x3f3f3f3f;
struct Round
{
    int x, y, z, r;
    Round(int x_ = 0, int y_ = 0, int z_ = 0, int r_ = 0) : x(x_), y(y_), z(z_), r(r_) {}
    bool operator<(const Round& rd) const
    {
        return x == rd.x ? (y == rd.y ? (z == rd.z ? (r < rd.r)
                                                   : (z < rd.z))
                                      : (y < rd.y))
                         : (x < rd.x);
    }
};

double getDis(const Round& r1, const Round& r2)
{
    int dis2 = 0;
    auto mult = [](int v1, int v2)
    {
        return (v1 - v2) * (v1 - v2);
    };
    dis2 += mult(r1.x, r2.x);
    dis2 += mult(r1.y, r2.y);
    dis2 += mult(r1.z, r2.z);

    return max(0.0, (sqrt(dis2) - r1.r - r2.r) * 10);
}
int main()
{
    std::ios::sync_with_stdio(false);
    int tmp, ttt = 1;
    while (cin >> tmp && tmp != -1)
    {
        vector<Round> rnds;
        vector<double> dis(MAXN, INF);
        for (int i = 0; i < tmp; i++)
        {
            int x, y, z, r;
            cin >> x >> y >> z >> r;
            rnds.push_back(Round(x, y, z, r));
        }
        for (int i = 0; i < 2; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            rnds.push_back(Round(x, y, z, 0));
        }
        auto s = rnds.size(), t = rnds.size();
        s -= 2;
        t -= 1;

        // dijkstra
        vector<bool> vis(rnds.size() + 2, false);
        dis[s] = 0;
        for (int cnt = 1; cnt < rnds.size(); cnt++)
        {
            size_t u = rnds.size();
            double minimal = INF;
            for (int i = 0; i < rnds.size(); i++)
            {
                if (!vis[i] && dis[i] < minimal)
                {
                    u = i;
                    minimal = dis[i];
                }
            }

            if (u == rnds.size())
            {
                break;
            }

            vis[u] = true;

            for (int i = 0; i < rnds.size(); i++)
            {
                if (i == u)
                {
                    continue;
                }
                dis[i] = min(dis[i], dis[u] + getDis(rnds[u], rnds[i]));
            }
        }

        cout << "Cheese " << ttt++ << ": Travel time = " << (int)(std::round(dis[t])) << " sec\n";
    }
    return 0;
}