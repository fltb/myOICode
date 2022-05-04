#include <ios>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::cin;
using std::cout;
using std::queue;
template <typename T> inline void read(T& t) {
    int f = 0, c = std::getchar(); t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f) t = -t;
}
template<typename T> inline
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T> inline
T min(T a, T b)
{
    return a < b ? a : b;
}
const int MAXN = 1000 + 2, MAXP = 1000 + 2;
const int mv[2][4] = {
    {-1, 0, 1, 0},
    { 0, 1, 0, -1}
};

int n, m;
int mp[MAXN][MAXN];
bool vis[MAXN][MAXN];

struct Point {
    int line, row;
    Point(int line_, int row_) : line(line_), row(row_) {}
};

bool judge(int val)
{
    queue<Point> bfs;
    bfs.push((Point(1, 1)));

    auto valid = [&val](const Point & point) {
        bool inRange = point.line > 0 && point.line <= n && point.row > 0 && point.row <= m;
        bool inCost = mp[point.line][point.row] <= val;
        bool visited = vis[point.line][point.row];

        return inRange && inCost && !visited;
    };

    while (!bfs.empty())
    {
        auto now = bfs.front();
        bfs.pop();

        for (int i = 0; i < 4; i++)
        {
            auto to = Point(now.line + mv[0][i], now.row + mv[1][i]);
            if (valid(to))
            {
                vis[to.line][to.row] = true;
                bfs.push(to);
                if (to.line == n)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    read(n);
    read(m);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            read(mp[i][j]);
        }
    }

    int l = 0, r = MAXP;
    int mid = (l + r) / 2, pos = r;
    while (l <= r)
    {
        mid = (l + r) / 2;
        for (int i = 0; i < MAXN; i++)
        {
            for (int j = 0; j < MAXN; j++)
            {
                vis[i][j] = false;
            }
        }
        if (judge(mid))
        {
            pos = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << pos << "\n";
    return 0;
}