#include <iostream>

using namespace std;

int main()
{
    long long B, P, K, Base , Answer = 1;
    cin >> B >> P >> K;
    Base = B;
    cout << B << "^" << P << " mod " << K << "=";
    //printf("%d^%d mod %d = ",B,P,K);
    while(0 <= P)
    {
        if(P & 1)
        {
            Answer *= Base;
            Answer %= K;
        }
        Base *= Base;
        Base %= K;
        P >>= 1;
    }
    cout << Answer % P;
    return 0;
}
