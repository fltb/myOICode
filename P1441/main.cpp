#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;

const int MAXN = 20,
          MAXM = 4,
          MAXA = 100;
int N, M, Ans;
int A[MAXN+2];

int bitcount (unsigned int n)
{
    int count=0 ;
    while (n) {
        count++ ;
        n &= (n - 1) ;
    }
    return count ;
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }
    for(int i = 0; i < (1<<N); ++i)
    {
        if(bitcount(i) == (N-M) )
        {
            bitset<MAXN * MAXA + 2> S;
            for(int b = 0; b < N; ++b)
            {
                if(i & (1 << b) )
                {
                    S[0] = 1;
                    S |= (S << A[b]);
                }
            }
            Ans = max(Ans, int(S.count() ) );
        }
    }
    cout << Ans-1;
}
