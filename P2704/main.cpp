/*
题目描述

司令部的将军们打算在 N×MN\times MN×M 的网格地图上部署他们的炮兵部队。

一个 N×MN\times MN×M 的地图由 NNN 行 MMM 列组成，地图的每一格可能是山地（用 H\texttt{H}H 表示），也可能是平原（用 P\texttt{P}P 表示），如下图。

在每一格平原地形上最多可以布置一支炮兵部队（山地上不能够部署炮兵部队）；一支炮兵部队在地图上的攻击范围如图中黑色区域所示：

如果在地图中的灰色所标识的平原上部署一支炮兵部队，则图中的黑色的网格表示它能够攻击到的区域：沿横向左右各两格，沿纵向上下各两格。

图上其它白色网格均攻击不到。从图上可见炮兵的攻击范围不受地形的影响。

现在，将军们规划如何部署炮兵部队，在防止误伤的前提下（保证任何两支炮兵部队之间不能互相攻击，即任何一支炮兵部队都不在其他支炮兵部队的攻击范围内），在整个地图区域内最多能够摆放多少我军的炮兵部队。
输入格式

第一行包含两个由空格分割开的正整数，分别表示 NNN 和 MMM。

接下来的 NNN 行，每一行含有连续的 MMM 个字符，按顺序表示地图中每一行的数据。
输出格式

一行一个整数，表示最多能摆放的炮兵部队的数量。
输入输出样例
输入 #1

5 4
PHPP
PPHH
PPPP
PHPP
PHHP

输出 #1

6

说明/提示

对于 100%100\%100% 的数据，N≤100N\le 100N≤100，M≤10M\le 10M≤10，保证字符仅包含 p 与 h。

*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
const int MAXN = 100, MAXM = 10;

int dp[65][65][3], // dp[上一行状态][这一行状态][这一行] = 当前状态的值
    pre_val[65], // pre_val[光标] = 预处理的合理状态值
    pre_num[65], // pre_num[光标] = 光标对应状态中 1 的个数
    graph[MAXN+2], //每行的图像的状态的二进制
    n, m, cnt, ans;

int bit_count(unsigned int x)
{
    int bits = 0;
    while (x)
    {
        ++bits;
        x &= (x-1);
    }
    return bits;
}

void pre_all()
{
    cnt++;
    for (int i = 1; i < (1<<m); ++i)
    {
        if (!(i & ( (i>>1) | (i>>2) ) ) )
        {
            pre_val[cnt]   = i;
            pre_num[cnt++] = bit_count(i);
        }
    }
}

int main()
{
    cin >> n >> m;
    //预处理图像到状态
    for (int i = 1; i <= n; ++i)
    {
        char ch1[MAXM+2];
        scanf("%s", &ch1);
        for(int j = 0; j < m; ++j)
        {
            graph[i] = (graph[i]<<1) + ('H' == ch1[j]);
        }
    }

    pre_all();

    //特殊对待第 1 2 行
    for (int si = 0; si < cnt; ++si)
    {
        int x = pre_val[si];
        if (!(graph[1] & x) )
        {
            dp[cnt][si][1] = pre_num[si];
            for (int sj = 0; sj < cnt; ++sj)
            {
                int y = pre_val[sj];
                if ( !( x & y ) && !(graph[2] & y) )
                {
                    dp[si][sj][2] = dp[cnt][si][1] + pre_num[sj];
                }
            }
        }

    }
    // dp 主体部分
    for (int i = 3; i <= n; ++i)
    {
        for (int snow = 0; snow < cnt; ++snow) // snow 这一行 si 上两行 sj 上一行
        {
            int now = pre_val[snow];
            if (!(now & graph[i]) )
            {
                for (int si = 0; si < cnt; ++si)
                {
                    int x = pre_val[si];
                    if(!(x & graph[i-2]) )
                    {
                        for (int sj = 0; sj < cnt; ++sj)
                        {
                            int y = pre_val[sj];
                            if ( !( (y & graph[i-1]) || (y & x) || (now & x) || (now & y) ) )
                            {

                                dp[sj][snow][i%3] = std::max(dp[si][sj][(i-1)%3] + pre_num[snow],
                                                      dp[sj][snow][i%3]);
                                //cout<<x<<" "<<y<<" "<<now<<" "<<i<<" "<<dp[sj][snow][i%3]<<endl;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int si = 0; si < cnt; ++si)
    {
        for(int sj = 0; sj < cnt; ++sj)
        {
            ans = std::max(ans, dp[si][sj][n%3]);
        }
    }
    cout << ans;
}
