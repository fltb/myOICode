#include <iostream>
#include <algorithm>
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
/*
考虑进行 模拟。
aaaba -> aaaa
ababbb -> aabb || bbbb
abbbbbba -> bbbbbb
abcdcd -> cc || dd
问题： 如何判断合法？
记录先前的值，然后类似括号匹配的方式，一对匹配了，先前那些都不要了。

具体的
*/

const int CHARNUM = 27;
bool flags[CHARNUM];

inline bool valid(char ch)
{
    return ch >= 'a' && ch <= 'z';
}
inline void clearin()
{
    while (!valid(cin.peek()))
    {
        cin.get();
    }
}
inline void clearFlag()
{
    for (int i = 0; i < CHARNUM; i++)
    {
        flags[i] = false;
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n = 0, m = 0;
        clearin();
        clearFlag();
        while (valid(cin.peek()))
        {
            char ch;
            cin >> ch;
            if (flags[ch - 'a'])
            {
                m += 2;
                clearFlag();
            }
            else
            {
                flags[ch - 'a'] = true;
            }
            n++;
        }
        cout << n - m << "\n";
    }
    return 0;
}