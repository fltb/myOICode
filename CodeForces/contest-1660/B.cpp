#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
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
int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;

        std::vector<int> a;
        for (int i = 0; i < n; i++)
        {
            int now;
            cin >> now;
            a.push_back(now);
        }
        std::sort(a.begin(), a.end());
        if (n == 1)
        {
            cout << (a[0] > 1 ? "NO" : "YES") << "\n";
        }
        else
        {
            cout << (a[n-2] + 1 < a[n-1] ? "NO" : "YES") << "\n";
        }

    }
    return 0;
}