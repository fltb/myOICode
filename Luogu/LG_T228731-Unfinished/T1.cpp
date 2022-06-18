#include <iostream>
#include <algorithm>
#include <cmath>
using std::log10;
using std::cin;
using std::cout;
template<typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}
const char VALID [] = "aya",
           INVALID [] = "baka";
const long long BAKANUN [] = {
    1,
    9 ,
    99 ,
    9999 ,
    99999 ,
    999999 ,
    9999999 ,
    99999999 ,
    999999999 ,
    9999999999 ,
    99999999999 ,
    999999999999 ,
    9999999999999
};


int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> k >> n;
        if (n % BAKANUN[k] == 0)
        {
            cout << VALID << "\n";
        }
        else
        {
            cout << INVALID << "\n";
        }
    }
}