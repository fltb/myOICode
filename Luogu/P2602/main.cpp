#include <iostream>
#include <algorithm>
#include <cmath>
using std::cin;
using std::cout;
using std::pow;
typedef long long ll;
const int LENGTH = 12 + 2;

ll arrTable[LENGTH];

void init()
{
    arrTable[1] = 1;
    for (int len = 2; len < LENGTH; len++)
    {
        arrTable[len] = arrTable[len - 1] * 10 + (ll)pow(10, len - 1);
    }
}

ll numBit[LENGTH],
   numCut[LENGTH],
   arr[LENGTH][10];
int solve(ll a)
{
    // clear begin::
    for (int i = 0; i < LENGTH; i++)
    {
        numBit[i] = 0;
        numCut[i] = 0;
        for (int j = 0; j < 10; j++)
        {
            arr[i][j] = 0;
        }
    }
    // clear end::

    // get b len begin::
    int cnt = 0;
    /*
    100 -> 1, 10, 100
    */
    ll b = a;
    while (b > 0)
    {
        numBit[++cnt] = b % 10;
        b /= 10;
    }
    for (int i = 1; i <= cnt; i++)
    {
        numCut[i] = a % (ll)pow(10, i);
        numCut[i]++;
    }
    // get b len end::

    // dp begin::
    // init
    for (int i = 0; i <= numBit[1]; i++)
    {
        arr[1][i] = 1;
    }

    // main
    for (int len = 2; len <= cnt; len++)
    {
        for (int i = 0; i < 10; i++)
        {
            arr[len][i] = numBit[len] * arrTable[len - 1] + arr[len - 1][i];
            if (i < numBit[len])
            {
                arr[len][i] += (ll)pow(10, len -1);
            }
            else if (i == numBit[len])
            {
                arr[len][i] += numCut[len - 1];
            }
        }
    }

    // clean 0
    for (int len = cnt; len > 1; len--)
    {
        for (int i = len; i <= cnt; i++)
        {
            arr[i][0] -= pow(10, len - 1);
        }
    }
    // dp end::
    if (a == 0)
    {
        cnt = 1;
    }
    return cnt;
}

ll ans[10];
int main()
{
    init();
    ll a, b;
    cin >> a >> b;
    int cnt = solve(b);
    for (int j = 0; j < 10; j++)
    {
        ans[j] = arr[cnt][j];
    }
    cnt = solve(a - 1);
    for (int j = 0; j < 10; j++)
    {
        ans[j] -= arr[cnt][j];
        cout << ans[j] << ((j == 9) ? "\n" : " ");
    }
    return 0;
}