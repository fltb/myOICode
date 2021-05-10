#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100 + 3, MAXA = 1000 + 3;

int A[MAXN], F[MAXA],
    N, M;

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; ++i)
    {
        scanf("%d",&A[i]);
    }
    sort(A+1,A+N+1);
    F[0] = 1;
    for(int i = 1; i <= N; ++i)
    {
        for(int j = M; A[i] <= j; --j)
        {
            F[j] += F[j-A[i]];
        }
    }
    cout << F[M];
    return 0;
}
