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
const int MAXN = 100 + 2, MAXM = 2000 + 2, MOD = 998244353;
template <typename T>
void update(T & val, const T & addVal)
{
    val = (val + addVal) % MOD;
}
/*
-------食材
|
|
|
|
方法

限制条件
    - 至少选择一个 Emiya 不会让大家饿肚子，所以将做至少一道菜，即 k≥1
    - 每一行最多选一个 Rin 希望品尝不同烹饪方法做出的菜，因此她要求每道菜的烹饪方法互不相同 
    - 每一列选不超过一半 Yazi 不希望品尝太多同一食材做出的菜，因此他要求每种主要食材至多在一半的菜（即 Math.floor(k/2) )中被使用

过程：
    - 先标记不合法的一行
    - 然后一列一列选择下去
        枚举当前列
        由于当前列只能选择一个，所以枚举这个能不能选就行了
        然后通过选择几个有几种方法，一步步加上去
    input [方法][食物], sum[方法]
    f[方法][特殊食物数量][其他食物数量]
*/
int input[MAXN][MAXM], sum[MAXN];
long long f[2][MAXN][MAXN];
int main()
{
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;

    long long total = 1, wrong = 0;
    for (int i = 1; i <= n; i++)
    {
        sum[i] = 0;
        for (int j = 1; j <= m; j++)
        {
            cin >> input[i][j];
            sum[i] = (sum[i] + input[i][j]) % MOD;
        }
        total = total * (sum[i] + 1) % MOD;
    }

    for (int food = 1; food <= m; food++)
    {
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                f[0][i][j] = f[1][i][j] = 0;
            }
        }

        f[0][0][0] = 1;

        // 枚举不同方法
        for (int method = 1; method <= n; method++)
        {
            for (int mainFoodMethod = 0; mainFoodMethod <= method; mainFoodMethod++)
            {
                for (int otherFoodMethod = 0; otherFoodMethod <= method - mainFoodMethod; otherFoodMethod++)
                {
                    const int me = method % 2, pme = (method + 1) % 2, mf = mainFoodMethod, of = otherFoodMethod;

                    f[me][mf][of] = f[pme][mf][of];
                    if (mf > 0)
                    {
                        update(f[me][mf][of], f[pme][mf - 1][of] * input[method][food] % MOD);
                    }
                    if (of > 0)
                    {
                        update(f[me][mf][of], f[pme][mf][of - 1] * ((sum[method] - input[method][food] + MOD) % MOD) % MOD);
                    }
                }
            }
        }
        for (int mainFoodMethod = 1; mainFoodMethod <= n; mainFoodMethod++)
        {
            for (int otherFoodMethod = 0; otherFoodMethod <= n - mainFoodMethod; otherFoodMethod++)
            {
                if (mainFoodMethod > otherFoodMethod)
                {
                    update(wrong, f[n%2][mainFoodMethod][otherFoodMethod]);
                }
            }
        }
    }

    cout << (total - 1 - wrong + MOD) % MOD << "\n";
    return 0;
}