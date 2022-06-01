#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <utility>
using std::cin;
using std::cout;
using std::strcpy;
using std::strlen;
using std::strcmp;
using std::islower;
using std::log2;
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
const int MAXN = 15, MAXS = 50 + 2, MOD = 1000003;

inline auto getBits(int x)
{
    auto cnt = 0;
    while(x > 0)
    {
        cnt++;
        x &= x - 1;
    }
    return cnt;
}

int n, k, l;

int total, upLimit, record[MAXN], cnt;
std::string input[MAXN];
void dfs(int now, int has)
{
    if (now == n + 1)
    {
        if (has != upLimit)
        {
            return;
        }
        long long tmpVal = 1ll;
        for (int j = 0; j < l; j++)
        {
            char la = '?';
            for (int i = 1; i <= upLimit; i++)
            {
                    if (input[record[i]][j] != '?')
                    {
                        if (la == '?')
                        {
                            la = input[record[i]][j];
                        }
                        else if (la != input[record[i]][j])
                        {
                            return;
                        }
                    }
            }
            if (la == '?')
            {
                tmpVal = tmpVal * 26 % MOD;
            }
        }
        total += tmpVal;
        total %= MOD;
        return;
    }
    if (has < upLimit)
    {
        record[++cnt] = now;
        dfs(now + 1, has + 1);
        record[cnt--] = 0;
    }
    if (n - now >= upLimit - has)
    {
        dfs(now + 1, has);
    }
}
/*
学了容斥之后回来的
二个循环
第一个生成字符串 统计对应的式子匹配上的数量的情况数量
第二个统计答案*/
int main()
{
    std::ios::sync_with_stdio(false);
    int C[MAXN][MAXN];
    for (int i = 0; i < MAXN; i++)
    {
        C[i][0] = 1;
        for (int j = 0; j <= i; j++)
        {
            // C(n, m) = C(n-1, m-1) + C(n-1, m)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }

    int t;
    cin >> t;
    while(t--)
    {
        long long ans[MAXN];
        for (int i = 0; i < MAXN; i++)
        {
            ans[i] = 0;
        }
        cin >> n >> k;

        auto cnting = 1;
        while (cnting <= n)
        {
            std::string line;
            std::getline(cin, line);
            cin.get();
            if (line != "")
            {
                input[cnting] = line;
                cnting++;
            }
        }
        l = input[0].length();

        // 最后容斥答案
        for (int i = n; i >= k; i--)
        {
            upLimit = i;
            total = 0;
            dfs(1, 0);
            auto sum = 0ll;
            for (int j = i + 1; j <= n; j++)
            {
                sum = (sum + C[j][i] * ans[j] % MOD) % MOD;
            }
            ans[i] = (total + MOD - sum) % MOD;
        }
        cout << ans[k] << "\n";
    }
    
    return 0;
}

/*
1100
1100-1110-1101+1111

1110
*/