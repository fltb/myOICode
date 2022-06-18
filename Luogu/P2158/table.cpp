#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;

const int MAXN = 40000+2;

int eular(int num)
{
    int ans = num;
    for (int i = 2; i*i <= num; ++i)
    {
        if (num % i == 0)
        {
            ans -= ans/i;
            while(num % i == 0)
            {
                num /= i;
            }
        }
    }
    if (num > 1)
    {
        ans -= ans/num;
    }
    return ans;
}

int main()
{
    int n;
    cin >>n;
    int ans = 0;
    for (int i = 1; i < n; ++i)
    {
        ans += eular(i);
    }
    cout << ans*2+1 << "\n";

    return 0;
}
