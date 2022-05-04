#include <ios>
#include <iostream>
#include <cstdio>
#include <algorithm>
using std::cin;
using std::cout;
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
const int MAXN = 50000 + 2, MAXL = 1000000000 + 2;

int sum[MAXN];
int l, n, m;

bool judge(int length)
{
    int cnt = 0;
    int pre = 0;
    for (int i = 1; i <= n; i++)
    {
        if (sum[i] - sum[pre] < length)
        {
            cnt++;
            if (cnt > m)
            {
                return false;
            }
        }
        else
        {
            pre = i;
        }
    }
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> l >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> sum[i];
    }
    sum[++n] = l;
    // 对答案进行二分
    int lc = 0, rc = MAXL;
    int mid = (lc + rc) / 2, pos = rc + 1;
    while (lc <= rc)
    {
        mid = (lc + rc) / 2;
        if (judge(mid))
        {
            pos = mid;
            lc = mid + 1;
        }
        else
        {
            rc = mid - 1;
        }
    }
    cout << pos << "\n";
    return 0;
}