#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::string;
const int MAXS = 100+2;

int square(int x)
{
    return x*x;
}

double get_dis(int x1, int y1, int x2, int y2)
{
    return std::sqrt(square(x1 - x2) + square(y1 - y2));
}

struct Point
{
    int x, y, t, city;
    Point(){}
    Point(int xx, int yy, int tt, int c) : x(xx), y(yy), t(tt),city(c) {}
};

double get_val(const Point & a, const Point & b, int t)
{
    if (a.city == b.city)
    {
        return get_dis(a.x, a.y, b.x, b.y)*a.t;
    }
    else
    {
        return get_dis(a.x, a.y, b.x, b.y)*t;
    }
}

int main()
{
    int n;
    cin >> n;
    while (n > 0)
    {
        --n;
        int s, t, a, b;
        cin >> s >> t >> a >> b;
        std::vector<Point> points((s + 2)*4);
        std::vector<std::vector<double> > floyd( 4*(s + 2), std::vector<double>(4*(s + 2), 2147483647));
        for (int i = 0; i < s; ++i)
        {
            int x1, y1, x2, y2, x3, y3, tt;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> tt;
            int ab = square(x1-x2) + square(y1-y2);
            int bc = square(x2-x3) + square(y2-y3);
	        int ac = square(x1-x3) + square(y1-y3);
            int x4, y4;  
            if (ab + ac == bc)
            {
                x4 = x2 + x3 - x1;
                y4 = y2 + y3 - y1;
            }
            if (ab + bc == ac)
            {
                x4 = x1 + x3 - x2;
                y4 = y1 + y3 - y2;
            }
            if (bc + ac == ab) 
            {
                x4 = x1 + x2 - x3;
                y4 = y1 + y2 - y3;
            }
            points[4*i]   = Point(x1, y1, tt, i+1);
            points[4*i+1] = Point(x2, y2, tt, i+1);
            points[4*i+2] = Point(x3, y3, tt, i+1);
            points[4*i+3] = Point(x4, y4, tt, i+1);
        }

        /*if (a == b)
        {
            double ans = 2147483647;
            for (int i = 4*(a-1); i < 4 * a; ++i)
            {
                for (int j = 4*(b-1); j < 4 * b; ++j)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    ans = std::min(ans, get_val(points[i], points[j], t));
                }
            }
            cout << std::fixed << std::setprecision(1) << ans << endl;
            continue;
        }*/

        for (int i = 0; i < 4*s; ++i)
        {
            for (int j = 0; j < 4*s; ++j)
            {
                if (i == j)
                {
                    continue;
                }
                floyd[i][j] = get_val(points[i], points[j], t);
            }
        }

        for (int k = 0; k < 4*s; ++k)
        {
            for (int i = 0; i < 4*s; ++i)
            {
                if (i == k)
                {
                    continue;
                }
                for (int j = 0; j < 4*s; ++j)
                {
                    if (i == j || j == k)
                    {
                        continue;
                    }
                    if (floyd[i][j] > floyd[i][k] + floyd[k][j])
                    {
                        floyd[i][j] = floyd[i][k] + floyd[k][j];
                    }
                }
            }
        }
        double ans = 2147483647;
        for (int i = 4*(a-1); i < 4 * a; ++i)
        {
            for (int j = 4*(b-1); j < 4 * b; ++j)
            {
                ans = std::min(ans, floyd[i][j]);
            }
        }
        if (s == 1) // 我实在不理解这样的操作
        {
            ans = 0;
        }
        cout << std::fixed << std::setprecision(1) << ans << endl;
    }
    return 0;
}

