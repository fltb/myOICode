#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <ostream>
using std::cin;
using std::cout;
using std::sort;
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
const int MAXN = 2e5 + 2;
struct NodeJS
{
    int l, r;
    NodeJS(int l_ = 0, int r_ = 0) : l(l_), r(r_) {}
    bool operator<(const NodeJS& x)
    {
        return l + max(r, x.l) + x.r < x.l + max(x.r, l) + r;
    }
};
const auto& operator>>(const std::istream& is, NodeJS& nd)
{
    cin >> nd.l >> nd.r;
    return is;
}
NodeJS nds[MAXN];
int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> nds[i];
    }

    sort(&nds[0], &nds[n]);

    long long ans = 0ll;
    int las = 0;
    for (int i = 0; i < n; i++)
    {
        ans += max(las, nds[i].l);
        las = nds[i].r;
    }
    ans += las;

    cout << ans << '\n';

    return 0;
}