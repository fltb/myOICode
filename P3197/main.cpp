#include <iostream>

using namespace std;
const int MOD = 100003;

long long QAAAA(long long a, long long b)
{
    long long base = a,
        ans  = 1;
    while(b > 0)
    {
        if(b & 1)
        {
            ans *= base;
            ans %= MOD;
        }
        base *= base;
        base %= MOD;
        b >>= 1;
    }
    return ans % MOD;
}


int main()
{
    long long M, N;
    cin >> M >> N;
    cout << ( QAAAA(M, N) - (M % MOD)*QAAAA(M-1,N-1)%MOD + MOD )%MOD;
    return 0;
}
