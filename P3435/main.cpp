#include <ios>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;
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
    int n;
    string str;
    
    cin >> n;
    cin.get();
    cin >> str;
    n = str.length();
    vector<int> kmp(n+1, -1);
    int k = -1;
    for (int i = 1; i < n; i++)
    {
        while (k > -1 && str[k + 1] != str[i])
        {
            k = kmp[k];
        }
        if (str[k + 1] == str[i])
        {
            k++;
        }
        kmp[i] = k;
    }
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (kmp[j] > -1)
        {
            j = kmp[j];
        }
        if (kmp[i] != -1)
        {
            kmp[i] = j;
        }
        ans += (i - j);
    }
    cout << ans << "\n";
    return 0;
}