#include <iostream>
using std::cin;
using std::cout;
int gcd(int a, int b) {
    return b > 0 ? gcd(b, a % b) : a;
}
const int MAXN = 200000 + 2;

int fa[MAXN], val[MAXN];

int dfs(int x, int v)
{
    if (x == 0)
    {
        return -1;
    }
    if (gcd(val[x], v) > 1)
    {
        return x;
    }
    return dfs(fa[x], v);
}

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) 
    {
        cin >> val[i];
    }

    for (int i = 1; i < n; ++i)
    {
        int f, s;
        cin >> f >> s;
        fa[s] = f;
    }

    for (int i = 1; i <= k; ++i)
    {
        int md;
        cin >> md;
        if (md == 1)
        {
            int ui;
            cin >> ui;
            cout << dfs(fa[ui], val[ui]) << "\n";
        }
        else
        {
            int ui, vi;
            cin >> ui >> vi;
            val[ui] = vi;
        }
    }
    return 0;
}