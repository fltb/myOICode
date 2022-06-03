#include <ios>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::string;
template <typename T> inline void read(T& t) {
    int f = 0, c = std::getchar(); t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f) t = -t;
}
template<typename T> inline
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T> inline
T min(T a, T b)
{
    return a < b ? a : b;
}
int main()
{
    std::ios::sync_with_stdio(false);
    string s1;
    int aaa;
    cin >> aaa;
    cin.get();
    cin >> s1;
    vector<int> kmp(s1.size(), 0);
    int k = 0;
    int ans = 0;
    for (int i = 1; i < s1.size(); ++i)
    {
        while (k > 0 && s1[k] != s1[i])
        {
            k = kmp[k - 1];
        }
        if (s1[k] == s1[i])
        {
            k++;
        }
        kmp[i] = k;
    }
    cout << s1.length()-kmp[s1.length()-1] << "\n";
    return 0;
}