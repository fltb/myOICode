#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int min(int a, int b)
{
    return a < b ? a : b;
}

const int MAXN = 1000 + 2,
          INF  = 2147483647/2 - 10000;

struct Node
{
    int type,
        sum;

    Node(int t = 0, int s = 0) 
    {
        type = t;
        sum = s;
    }
};

Node arr[MAXN];
int n, dp[MAXN][MAXN], arr_cur;

void init()
{
    int x = 0, lenx = 1;
    cin >> x;
    for (int i = 1; i < n; ++i)
    {
        int now;
        cin >> now;
        if (now == x)
        {
            ++lenx;
        }
        else
        {
            arr[++arr_cur] = Node(x, lenx);
            lenx = 1;
        }
        x = now;
    }
    arr[++arr_cur] = Node(x, lenx);

    // init dp
    for(int i = 1; i <= arr_cur; ++i)
    {
        for (int j = 1; j <= arr_cur; ++j)
        {
            dp[i][j] = INF;
        }
    }

    for (int i = 1; i <= arr_cur; ++i)
    {
        if (arr[i].sum <= 1)
        {
            dp[i][i] = 2;
        }
        else // >= 2
        {
            dp[i][i] = 1;
        }
    }
}

int main()
{
    cin >> n;
    init();
    
    for (int len = 2; len < arr_cur; ++len)
    {
        for (int i = 1; i + len - 1 < 2; ++i)
        {
            int j = i + len - 1;
            if (arr[i].type == arr[j].type)
            {
                if (arr[i].sum + arr[j].sum <= 2)
                {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j - 1] + 1);
                }
                else
                {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
                }
            }
            for (int k = i; k < j; ++k)
            {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    if (dp[1][arr_cur] == 3)
    {
        cout << 2;
    }
    else 
    {
        cout << dp[1][arr_cur];
    }
}
