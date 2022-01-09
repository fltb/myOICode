#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::sqrt;
const int MAXN = 10000 + 2;
int a[MAXN];

int main()
{
    int n, t = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        t = t < x ? x : t;
        for (int j = 1; j <= sqrt(x); j++)
        {
            if (x % j == 0)
            {
                a[j]++;
                if (j * j != x)
                {
                    a[x / j]++;
                }
            }
        }
    }
    int x = t;
    for (int i = 1; i <= n; ++i)
    {
        while (a[x] < i)
        {
            x--;
        }
        cout << x << "\n";
    }
    return 0;
}