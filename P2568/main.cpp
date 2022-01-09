#include <iostream>
#include <vector>
#include <cmath>
using std::cin;
using std::cout;
using std::vector;
using std::sqrt;
/*
思路：
已知： 若 gcd(a, b) == 1 则 gcd(a * p, b * p) == p (p 为质数)
*/

int gcd(int a, int b)
{
    return b > 0 ? gcd(b, a % b) : a;
}

void get_prime(vector<int> & v, int n)
{
    // 先假设全部是质数
    vector<bool> tmp = vector<bool>(n + 2, true);
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (tmp[i])
        {
            for (int j = 1; i * j <= n; ++j)
            {
                tmp[i * j] = false;
            }
        }
    }
    // 现在质数是 true，偶数 false
    for (int i = 2; i <= n; i++)
    {
        if (tmp[i])
        {
            v.push_back(i);
        }
    }
}

void Eular(vector<long long> & euler, int n)
{
    euler = vector<long long>(n + 2, 0);
    euler[1] = 1;
    int cnt = 0;
    vector<bool> vis = vector<bool>(n + 2, false);
    for(int i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            euler[++cnt] = i;
        }
        for (int j = 1; j <= cnt; j++)
        {
            if (i * euler[j] > n)
            {
                break;
            }
            vis[i * euler[j]] = true;
            if (i % euler[j] == 0)
            {
                break;
            }
        }
    }
}
int main()
{
    int n;
    vector<int> primes;
    cin >> n;
    get_prime(primes, n);
    vector<long long> eular;
    Eular(eular, n);
}