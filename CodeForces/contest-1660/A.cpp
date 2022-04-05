#include <ios>
#include <iostream>
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
        int a,b;
        cin >> a >> b;
        if (a == 0)
        {
            cout << "1\n";
            continue; 
        }
        cout << a + 2 * b + 1 << "\n";
    }
    return 0;
}