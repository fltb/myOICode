#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::getline;
using std::stack;
using std::string;
using std::vector;
const int MOD = 1000000007;
int main()
{
    std::ios::sync_with_stdio(false);
    int t;
    cin >> t;
    cin.get();
    while (t--)
    {
        string sBase;
        getline(cin, sBase);
        int n = sBase.length();
        sBase = sBase;
        vector<long long> kmp(sBase.length() + 1, 0);
        vector<long long> jump(sBase.length() + 1, 0);
        auto k = 0;
        jump[1] = 1;
        for (auto i = 1; i < n; i++)
        {
            while (k > 0 & sBase[k] != sBase[i])
            {
                k = kmp[k];
            }
            k += int(sBase[k] == sBase[i]);
            kmp[i + 1] = k;
            jump[i + 1] = jump[k] + 1;
        }
#ifdef FLOATINGBLOCKS
        auto prt = [&](vector<long long>& pt)
        {
            for (int i = 0; i < sBase.length(); i++)
            {
                cout << pt[i] << " ";
            }
            cout << '\n';
        };

        prt(kmp);
        prt(jump);
        cout << std::endl;
#endif
        int j = 0;
        long long ans = 1ll;
        for (auto i = 0; i < n; i++)
        {
            while (j > 0 && sBase[j] != sBase[i])
            {
                j = kmp[j];
            }
            j += int(sBase[j] == sBase[i]);
            while (j * 2 > i + 1)
            {
                j = kmp[j];
            }
            ans = ans * (jump[j] + 1) % MOD;
        }
        cout << ans << "\n";
    }
    return 0;
}

/*
0 0 1 2 3 
0 1 2 3 4 
36
0 0 
0 1 
1
0 0 0 0 1 2 1 2 1
0 1 1 1 2 2 2 2 
32

0 0 1 2 3 
0 0 1 2 3 
4
0 0 
0 0 
1
0 0 0 0 1 2 1 2 
0 0 1 1 1 2 1 2 
8*/