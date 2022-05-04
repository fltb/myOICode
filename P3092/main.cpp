#include <ios>
#include <iostream>
#include <cstdio>
#include <algorithm>
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
const int MAXN = 100000 + 2, MAXK = 16;
/*
    回顾状态压缩
    一个是把状态记在 dp 方程里面，一个是直接用状态定义 dp 数组

    前缀和优化

    需要到达 n 的时候留下最多的钱

    dp 定义

    dp[硬币的状态] = 到达的位置

    一个硬币是从上一个硬币转移过来的。
    转移的时候， 需要知道上次在第几，这次最大又能到第几

    硬币状态为 xxx 的时候，到了第几

    应该不会出现小的还要比大的好吧。
    
    那么转移开始！

    for i in [1, 1<<k) // 状态
        试着从它的子状态开始转移
        for j in 子状态
            dp[i] = max(dp[i], dp[j] + 更新的值)
            更新值： 二分前缀和找到**最靠右**的**符合**的值 (最靠左的不符合的值)
*/
int coins[MAXK], sum[MAXN], dp[(1 << MAXK) + 5];

int upperSreach(int val, int lc, int rc)
{
    int l = lc, r = rc;
    int mid = (l + r) / 2, pos = r + 1;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (sum[mid] - sum[lc - 1] > val)
        {
            pos = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return pos;
}

int main()
{
    int n, k;
    read(k), read(n);
    for (int i = 0; i < k; i++)
    {
        read(coins[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        read(sum[i]);
        sum[i] += sum[i-1];
    }

    int ans = -1;
    /*
        这个部分重新解释一下吧

        state 是状态 childState 子状态
        dp 存的是上一次到了哪里， 默认是 0，就是开始之前
        sum 是一个前缀和
        allowedVal 是当前允许的最大值
        二分到最靠右的小于等于 allowedVal 的值
        如果已经到最右边，就更新 ans
    */
    for (int state = 1; state < (1 << k); state++)
    {
        for (int bit = 0; bit < k; bit++)
        {
            if ((1 << bit) & state)
            {
                const int childState = (state ^ (1 << bit));
                int lc = dp[childState] + 1, rc = n;

                int pos = upperSreach(coins[bit], lc, rc) - 1;
                dp[state] = max(dp[state], pos);
                if (pos == n)
                {
                    int cnt = 0;
                    for (int bit = 0; bit < k; bit++)
                    {
                        if (!(state & (1 << bit)))
                        {
                            cnt += coins[bit];
                        }
                    }
                    ans = max(ans, cnt);
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}