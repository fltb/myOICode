#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int MAXN = 2 * 100000 + 5;
int A [MAXN] , f [MAXN], N, MaxAns = -0x7fffffff;
int main()
{
    cin>>N;
    for(int i = 1; i <= N; ++i)
    {
        scanf("%d", &A[i]);
        f[i] = max(f[i - 1] + A[i], A[i]);
        MaxAns = max(MaxAns,f[i]);
    }
    cout<<MaxAns;
    return 0;
}
