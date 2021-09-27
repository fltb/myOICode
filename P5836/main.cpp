#include <algorithm>
#include <iostream>
#include <cstdio>
using std::printf;
using std::scanf;
using std::cin;
using std::cout;
using std::endl;
const int MAXN = 100000 + 2;

char cows[MAXN];
int n, m, fa[MAXN], ans[MAXN], cnt;

int find(int x)
{
    if (fa[x] == x)
    {
        return x;
    }
    else
    {
        return fa[x] = find(fa[x]);
    }
}

void merge(int x, int  y)
{
    fa[find(x)] = find(y);
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        cin >> cows[i];
    }
    //cout << "In get" <<endl;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (cows[u] == cows[v])
        {
            merge(u, v);
            //printf("BBBBB %d\n", i);
        }
    }

    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        char c;
        cin >> a >> b >> c;
        if ( (find(a) == find(b) ) && cows[a] != c )
        {
            //printf("AAAAA %d\n", i);
            ans[i] = 0;
        }
        else
        {
            ans[i] = 1;
        }
    }

    for (int i = 1; i <= m; ++i)
    {
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
