#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
const long long fac [] = {
  1,
  1,
  2,
  6,
  24,
  120,
  720,
  5040,
  40320,
  362880,
  3628800,
  39916800,
  479001600,
  6227020800,
  87178291200,
  1307674368000,
  20922789888000,
  355687428096000,
  6402373705728000,
  121645100408832000,
  2432902008176640000,
};

int n;

long long contor(const vector<int> & x)
{
    long long sum = 0;
    for (size_t i = 1; i <= x.size(); ++i)
    {
        int cnt = 0;
        for (size_t j = i + 1; j <= x.size(); ++j)
        {
            if (x[j-1] < x[i-1])
            {
                cnt++;
            }
        }
        sum += fac[n - i] * cnt;
    }
    return sum + 1;
}

auto recontor(long long sum)
{
    vector<bool> vis(n + 2, false);
    vector<int> x;
    x.push_back(0);
    sum--;
    for (int i = 1; i <= n; ++i)
    {
        int tmp = sum / fac[n - i];
        int cur = 1;
        while (cur < n)
        {
            if (!vis[cur])
            {
                if (tmp <= 0)
                {
                    break;
                }
                tmp--;
            }
            cur++;
        }
        vis[cur] = true;
        x.push_back(cur);
        sum %= fac[n - i];
    }
    return x;
}

int main ()
{
    int k;
    cin >> n >> k;
    for (int ii = 0; ii < k; ++ii)
    {
        char ch;
        cin >> ch;
        if (ch == 'P') {
            long long sum;
            cin >> sum;
            auto x = recontor(sum);
            for (int i = 1; i <= n; ++i)
            {
                cout << x[i] << " ";
            }
            cout << "\n";
        } else if (ch == 'Q')
        {
            vector<int> x(n);
            for (int i = 0; i < n; ++i)
            {
                int a;
                cin >> a;
                x[i] = a;
            }
            cout << contor(x) << endl;
        }
    }
    return 0;
}
