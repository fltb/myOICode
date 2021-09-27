/*
题目描述

在N×N的棋盘里面放K个国王，使他们互不攻击，共有多少种摆放方案。国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各一个格子，共8个格子。

注：数据有加强（2018/4/25）
输入格式

只有一行，包含两个数N，K （ 1 <=N <=9, 0 <= K <= N * N）
输出格式

所得的方案数
输入输出样例
输入 #1

3 2

输出 #1

16

AC!
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
using std::bitset;
using std::cout; using std::cin; using std::endl;
const int MAXN = 9, INF = 0x7fffffff;

long long f[MAXN + 1][MAXN*MAXN + 10][(1<<MAXN) + 2] = {0};//f[第几行][这行加上前面有几个][这行的状态]
int n, k, num, pre_val[(1<<MAXN) + 2], pre_s[(1<<MAXN) + 2]; // pre_val[状态值] = 这个状态中 1 的个数， pre_s[num] = 一个状态

int count1(unsigned int a);
int pre_all();
int main()
{
    cin >> n >> k;
    pre_all();
    f[0][0][0] = 1;
    //dp starting
    for (int i = 1; i <= n; ++i)//at line i
    {
        for (int ni = 0; ni < num; ++ni) // state of line i
        {
            int si = pre_s[ni];
            for (int nj = 0; nj < num; ++nj)// state of line i - 1
            {
                int sj = pre_s[nj];
                if ( !( ( (sj<<1) | (sj>>1) | sj) & si ) ) // legaled
                {
                    for (int j = 0; j <= k; ++j) // j is used kings now
                    {
                        if (pre_val[si] <= j)
                        {
                            f[i][j][si] += f[i-1][j - pre_val[si] ][sj];
                            //cout<<i<<" is i "<<j<<" is j "<<j - pre_val[si]<<" is j - pre_val[si] "<<f[i-1][j - pre_val[si] ][sj]<<endl;
                        }
                    }
                    //cout << 111111<<endl;
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < num; ++i)//add the last line
    {
        ans += f[n][k][pre_s[i] ];
    }

    cout << ans << endl;
}

int count1(unsigned int a)
{
    int bits = 0;
    while (a)
    {
        a &= (a - 1);
        ++bits;
    }
    return bits;
}
int pre_all()
{
    for(int i = 0; i < (1<<n); ++i)
    {
        pre_val[i] = count1(i);
        if (!( ( (i<<1) | (i >>1) ) & i ) )
        {
            pre_s[num++] = i;
            //cout<<pre_val[i]<<" "<<num<<" "<<bitset<8>(i)<<endl<<endl;
        }
    }
}
