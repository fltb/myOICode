#include <ios>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using std::cin;
using std::cout;
using std::sqrt;
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
const double LIMIT = 0.001;
const int LEDGE = -100 - 2, REDGE = 100 + 2;
double a, b, c, d;
double f(double x)
{
    return a*x*x*x + b*x*x + c*x + d;
}
double search(double lc, double rc)
{
    auto l = lc, r = rc;
    auto mid = (l + r) / 2;
    if (f(lc) > 0) // 递增
    {
        while (l + LIMIT < r - LIMIT)
        {
            mid = (l + r) / 2;
            if (f(mid) < 0)
            {
                r = mid - LIMIT;
            }
            else
            {
                l = mid + LIMIT;
            }
        }
    }
    else // 递增
    {
        while (l + LIMIT < r - LIMIT)
        {
            mid = (l + r) / 2;
            if (f(mid) > 0)
            {
                r = mid - LIMIT;
            }
            else
            {
                l = mid + LIMIT;
            }
        }

    }
    return mid;
}
int main()
{    
    cin >> a >> b >> c >> d;

    double ji1 , ji2;
    {
        double aa = 3 * a, bb = 2 * b, cc= c;
        ji1 = (-bb - sqrt(bb * bb - 4 * aa * cc)) / (2 * aa);
        ji2 = (-bb + sqrt(bb * bb - 4 * aa * cc)) / (2 * aa);
    }

    std::printf("%.2f %.2f %.2f", search(LEDGE, ji1), search(ji1, ji2), search(ji2, REDGE));
    return 0;
}