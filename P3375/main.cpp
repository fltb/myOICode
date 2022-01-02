#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;

int main()
{
    string s1, s2;
    cin >> s1;
    cin >> s2;
    vector<int> kmp(s2.size(), 0);
    int k = 0;
    for (int i = 1; i < s2.size(); ++i)
    {
        while (k > 0 && s2[k] != s2[i])
        {
            k = kmp[k - 1];
        }
        if (s2[k] == s2[i])
        {
            k++;
        }

        kmp[i] = k;
    }

    int j = 0;
    for (int i = 0; i < s1.size(); ++i)
    {
        //cout << s1[i] << " j = " << j << " s2[j] = " << s2[j] <<"\n";
        while (j > 0 && s1[i] != s2[j])
        {
            j = kmp[j - 1];
        }
        if (s1[i] == s2[j])
        {
            j++;
        }
        if (j == s2.size())
        {
            cout << i - j + 2 << "\n";
            j = kmp[j - 1];
        }
    }

    for (int i = 0; i < kmp.size(); ++i)
    {
        cout << kmp[i] << ((i + 1 == kmp.size()) ? "\n" : " "); 
    }
    return 0;
}

/*
aaabaaabaaabaaabaaabaaabaaaa
aaaa
0123
*/