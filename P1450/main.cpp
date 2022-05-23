/*
# [HAOI2008]硬币购物

## 题目描述

共有 $4$ 种硬币。面值分别为 $c_1,c_2,c_3,c_4$。

某人去商店买东西，去了 $n$ 次，对于每次购买，他带了 $d_i$ 枚 $i$ 种硬币，想购买 $s$ 的价值的东西。请问每次有多少种付款方法。

## 输入格式

输入的第一行是五个整数，分别代表 $c_1,c_2,c_3,c_4, n$。

接下来 $n$ 行，每行有五个整数，描述一次购买，分别代表 $d_1, d_2, d_3, d_4,s$。

## 输出格式

对于每次购买，输出一行一个整数代表答案。

## 样例 #1

### 样例输入 #1

```
1 2 5 10 2
3 2 3 1 10
1000 2 2 2 900
```

### 样例输出 #1

```
4
27
```

## 提示

#### 数据规模与约定

* 对于 $100\%$ 的数据，保证 $1 \leq c_i, d_i, s \leq 10^5$，$1 \leq n \leq 1000$。
*/
#include <ios>
#include <iostream>
#include <cstdio>
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
/*
最简单的方法，枚举每次用几个
*/
const int MAXC = 4, MAXS = 1e5 + 2;

// ERR 没有 long long
long long pdp[MAXS];
int main()
{
    std::ios::sync_with_stdio(false);
    int c[MAXC + 1], n;
    for (int i = 1; i <= MAXC; i++)
    {
        cin >> c[i];
    }
    cin >> n;
    // 完全背包打表
    //ERR 忘了初始化 1 了
    pdp[0] = 1;
    for (int i = 1; i <= MAXC; i++)
    {
        for (int j = c[i]; j < MAXS; j++)
        {
            pdp[j] += pdp[j - c[i]];
        }
    }
    while (n--)
    {
        int s[MAXC + 1], v;
        for (int i = 1; i <= MAXC; i++)
        {
            cin >> s[i];
        }
        cin >> v;
        
        // ERR 没有 long long
        long long tot = pdp[v];
        // ERR st <<= 1 因为自己忘了枚举的是子集，以为是位移...
        for (int st = 1; st < (1 << 4); st++)
        {
            int weight = 0, cnt = 0;
            for (int bit = 0; bit < 4; bit++)
            {
                if ((1 << bit) & st)
                {
                    cnt++;
                    weight += (s[bit + 1] + 1) * c[bit + 1];
                }
            }
            if (weight <= v)
            {
                if (cnt % 2 != 0)
                {
                    tot -= pdp[v - weight];
                }
                else
                {
                    tot += pdp[v - weight];
                }
            }
        }
        cout << tot << "\n";
    }
    return 0;
}