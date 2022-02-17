#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
const int MAXN = 65 + 5;
int a[MAXN];
int n, sum = 0;
int next[MAXN];
bool findAns(int);
int main()
{
    cin >> n;
    int cnt = 0;
    while (n--)
    {
        int tmp;
        cin >> tmp;
        if (tmp > 50)
        {
            continue;
        }
        a[++cnt] = tmp;
        sum += tmp;
    }
    n = cnt;
    std::sort(a+1, a+1+n);
    for (int i = 2; i <= n; i++)
    {
        if (a[i] == a[i - 1])
        {
            next[i] = next[i - 1];
        }
        else
        {
            next[i] = i - 1;
        }
    }
    int max = a[n];
    for (int i = max; i <= sum; i++)
    {
        if (sum % i == 0)
        {
            if (findAns(i))
            {
                cout << i << "\n";
                return 0;
            }
        }
    }
}

bool used[MAXN], ok;
int tm, len;
void dfs(int k, int lenLeft, int last)
{
    int i = n;
    if (lenLeft < 0)
    {
        return;
    }
    if (lenLeft == 0)
    {
        if (k == tm)
        {
            ok = true;
            return; 
        }
        // to next
        while (i > 0)
        {
            if (!used[i])
            {
                break;
            }
            i--;
        }
        used[i] = true;
        dfs(k + 1, len - a[i], i);
        used[i] = false;

        if (ok)
        {
            return;
        }
    }

    i = std::upper_bound(a+1, a+1+last, lenLeft) - a - 1;

    while (i > 0)
    {
        while (i > 0)
        {
            if (!used[i])
            {
                break;
            }
            i--;
        }
        if (i == 0)
        {
            return;
        }
        used[i] = true;
        dfs(k, lenLeft - a[i], i);
        used[i] = false;
        if (ok)
        {
            return;
        }
        if (lenLeft == a[i])
        {
            return;
        }
        i = next[i];
    }
    // all used
    return;
}
bool findAns(int len)
{
    ::len = len;
    tm = sum / len;
    ok = false;
    used[n] = 1;
    dfs(1, len - a[n], n);
    used[n] = 0;
    return ok;
}
