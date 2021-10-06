#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
const int BITS = 17;

int max(int a, int b)
{
    return a < b ? b : a;
}

int main()
{
    int n, m;
    
    cin >> n >> m;

    int* f = new int[(n+2)*BITS];

    for (int i = 1; i <= n; ++i)
    {
        cin >> *(f + i*BITS);
    }

    for (int i = 1; i <= BITS; ++i)
    {
        for (int j = 1; j + (1<<i) - 1 <= n; ++j)
        {
            *(f + j*BITS + i) = max(*(f + j*BITS + (i-1)), *(f + (j + (1 << (i-1) ) )*BITS + (i-1)) );
        }
    }

    int l, r;
    while (m > 0)
    {
        --m;
        cin >> l >> r;
        int k = std::log2(r - l + 1);
        cout << max(*(f + l*BITS + k), *(f + (r-(1<<k) + 1)*BITS + k))<< endl;
    }

    delete [] f;
    return 0;
}
