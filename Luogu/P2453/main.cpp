#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
const int INF = 2147483647,
          MAXN = 200+2;
int min(int a, int b)
{
    return a < b ? a : b;
}
enum COST_FLAGS {
    DELETE, 
    REPLACE,
    COPY,
    INSERT,
    TWIDDLE
};
int cost_[5];
const int (&cost)[5] = cost_;
std::string str_from, str_to;
int get_kill_cost(int len)
{
    return len * cost[DELETE] - 1;
}

/*
返回使得 str_from 的下标 i 变成 str_to 的下标 j 所用的代价
*/
int rec[MAXN][MAXN];
void init_rec()
{
    for (int i = 0; i < MAXN; ++i)
    {
        for (int j = 0; j < MAXN; ++j)
        {
            rec[i][j] = INF;
        }
    }
}
int dfs(int i, int j) 
{
    int & rts = rec[i][j];
    if (rts != INF)
    {
        return rts;
    }
    if (str_from.size() <= i) // end
    {
        return (str_to.size() - j) * cost[INSERT];
    }
    if (str_to.size() <= j) // end
    {
        return get_kill_cost(str_from.size() - i);
    }
    if (str_from[i] == str_to[j])
    {
        rts = min(rts, dfs(i + 1, j + 1) + cost[COPY]);
    }
    if (str_from[i] == str_to[j + 1] && str_from[i + 1] == str_to[j])
    {
        rts = min(rts, dfs(i + 2, j + 2) + cost[TWIDDLE]);
    }
    rts = min(rts, dfs(i + 1, j) + cost[DELETE]);
    rts = min(rts, dfs(i + 1, j + 1) + cost[REPLACE]);
    rts = min(rts, dfs(i, j + 1) + cost[INSERT]);
    return rts;
}

int main()
{
    cin >> str_from >> str_to;
    for (int i = 0; i < 5; ++i)
    {
        cin >> cost_[i];
    }
    init_rec();
    cout << dfs(0, 0);
    return 0;
}
