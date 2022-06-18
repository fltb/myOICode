#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
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
struct NodeJS {
    int x, f, c;
    NodeJS(int x_=0, int f_=0, int c_=0) : x(x_), f(f_), c(c_) {}
};
const int MAXK = 10000 + 2, MAXE = 500 + 2;
const long long INF = 0x3f3f3f3f3f3f3f3f;
// 当前为 k 个时，花掉的最少价值
long long dp[2][MAXK];
NodeJS nds[MAXE];
int main()
{
    std::ios::sync_with_stdio(false);
    for (int i = 1; i < MAXK; i++)
    {
        dp[0][i] = dp[1][i] = INF;
    }
    int k, e, n;
    cin >> k >> e >> n;
    int xpre {0}, cn {0}, cp {1};
    for (int i = 1; i <= n; i++)
    {
        int x, f, c;
        cin >> x >> f >> c;
        nds[i] = NodeJS(x, f, c);
    }

    auto cmp = [](const NodeJS & a, const NodeJS & b) {
        return a.x < b.x;
    };
    std::sort(&nds[1], &nds[n+1], cmp);

    for (int i = 1; i <= n; i++) {
        NodeJS & nd = nds[i];
        const int dis = nd.x - xpre;
        xpre = nd.x;

        int x = nd.x, f = nd.f, c = nd.c;

        cn = !cn;
        cp = !cp;
        // 先做转移，就是直接把对应的搬过来
        for (int j = 0; j <= k; j++)
        {
            // j 吨，dis 公里
            const long long cost = (long long) j * j * dis;
            dp[cn][j] = min(INF, dp[cp][j] + cost);
            //cout << "Bring i = " << i << " j = " << j << " has cost :" << dp[cn][j] << std::endl;
        }
        for (int tme = 1; tme <= f; tme <<= 1)
        {
            //if (tme & f)
            {
                for (int j = k; j >= tme; j--)
                {
                    // 现在可以放进去 tme 个，先前搬来 j 个
                    const long long bring = j - tme;
                    const long long cost = (long long) tme * c;
                    dp[cn][j] = min(min(INF, dp[cn][bring] + cost), dp[cn][j]);
                    //cout << "At i = " << i << " j = " << j << " has cost :" << dp[cn][j] << std::endl;
                }
                f -= tme;
            }
        }
        for (int j = k; j >= f; j--)
        {
            // 现在可以放进去 tme 个，先前搬来 j 个
            const long long bring = j - f;
            const long long cost = (long long) f * c;
            dp[cn][j] = min(min(INF, dp[cn][bring] + cost), dp[cn][j]);
            //cout << "At i = " << i << " j = " << j << " has cost :" << dp[cn][j] << std::endl;
        }
    }

    const long long disFinal = e - nds[n].x;
    const long long ans = dp[n%2][k] + disFinal * k * k;
    cout << ans << "\n";
    return 0;
}
