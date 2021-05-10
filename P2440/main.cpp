#include <iostream>]
#include <cstdio>

using namespace std;
const int MAXN = 1e5 + 3, MAXR = 1e8 + 1;

int A[MAXN], N, K;

int main()
{
    cin >> N >> K;
    for(int i = 0; i < N; ++i)
    {
        scanf("%d", &A[i]);
    }

    int l = 0, r = MAXR, mid;
    while(l + 1 < r)
    {
        mid = (l + r)/2;
        int Cnt = 0;
        for(int i = 0; i < N; ++i)
        {
            Cnt += A[i]/mid;
        }
        if(Cnt >= K)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    cout << l;
    return 0;
}
