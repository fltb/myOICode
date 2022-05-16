#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::cin;
using std::cout;
using std::strcpy;
using std::strlen;
using std::strcmp;
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
const int MAXN = 15, MAXS = 50 + 1, MOD = 1000003;
struct NodeJS {
    int vue;
    char spring[MAXS];
    NodeJS(int v_=0, const char * src=nullptr) : vue(v_){
        if (src == nullptr)
        {
            strcpy(spring, "#");
        }
        else
        {
            strcpy(spring, src);
        }
    }
};

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

/*
考虑使用 dp 的做法
首先确定 dp[state] = { str, val}
一下情况转移：
    总体用暴力，总原理：
    Sum(符合 A 不符合 B) = Sum(符合 A ) - Sum (符合 A + B) 
    令 A + B = U
    这样只需要求恰好完全符合的了。

    下一步，统计符合状态 X 的总个数。
        设 Y 为上一状态，str 为 a??b??c
        当前的 str 为 a?bb???

        合并之后应该是 a?bb??c, val = 1 * 26 * 1 * 1 * 26 * 26 * 1
    还有要统计“炸了”的，即这种情况：
        aabc?a
        b?????
    res=###### val = 0

    那么每一步合并字符串 + 统计，如果失败就全部设置成 #
*/
NodeJS dp[1<<13];
int ans[1<<13];
int main()
{
    std::ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)
    {
        char input[MAXN][MAXS];

        int n, k;
        cin >> n >> k;

        auto cnting = 0;
        while (cnting < n)
        {
            char line [MAXS]; 
            cin.getline(line, MAXS);
            cin.get();

            if (strcmp(line,"") != 0)
            {
                strcpy(input[cnting], line);
                cnting++;
            }
        }
        auto l = strlen(input[0]);

        if (k > n) // failed
        {
            cout << "0\n";
            continue;
        }

        char strTmp[MAXS];
        for (int i = 0; i < l; i++)
        {
            strTmp[i] = '?';
        }
        strTmp[n] = '\0';
        dp[0] = NodeJS(0, strTmp);

        for (int st = 0; st < (1 << n); st++)
        {
            char * chNow = dp[st].spring;
            for (int bit = 0; bit < n; bit++)
            {
                const auto stBit = (1 << bit);
                if (stBit & st)
                {
                    const auto preSt = st ^ stBit;
                    const char * chPre = dp[preSt].spring;

                    if (chPre[0] == '#')
                    {
                        // 先前就不合法，自己也别挣扎了
                        strcpy(chNow, "#");
                        dp[st].vue = 0;
                        continue;
                    }

                    auto failed = false;
                    for (int i = 0; i < l; i++)
                    {
                        if (input[bit][i] != '?' && chPre[i] != '?' && input[bit][i] != chPre[i])
                        {
                            // 当前对应的串不相等了，而且都不是 ?，那就是完了（
                            failed = true;
                            break;
                        }
                        else
                        {
                            chNow[i] = input[bit][i];
                            if (chPre[i] != '?')
                            {
                                chNow[i] = chPre[i];
                            }
                        }
                    }

                    if (failed)
                    {
                        strcpy(chNow, "#");
                        dp[st].vue = 0;
                    }
                    else
                    {
                        auto vue = 1;

                        for (int i = 0; i < l; i++)
                        {
                            vue *= (chNow[i] == '?' ? 26 : 1);
                            vue %= MOD;
                        }

                        dp[st].vue = vue;
                    }

                    // 根据理想情况，那些子状态转过来的都是一样的，别的不算了
                    break;
                }
            }
        }

        // 开始按照开头的统计答案了
        auto aaa = 0;
        for (int st = 0; st < (1 << n); st++)
        {
            for (int stPre = 0; stPre < (1 << n); stPre++)
            {
                if (!((st ^ stPre) & st))
                {
                    const auto cnts = getBits(st ^ stPre);
                    ans[st] = (ans[st] + ((cnts >> 1) ? -1 : 1) * cnts * dp[stPre].vue + MOD) % MOD;
                    if (getBits(st) == n-k)
                    {
                        aaa += ans[st];
                    }
                }
            }
        }
        cout << aaa << "\n";
    }
    
    return 0;
}

/*

1100
1100-1110-1101+1111

1110

*/