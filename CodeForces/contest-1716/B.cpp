#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const
using std::cin;
using std::cout;
template <typename T>
inline void read(T& t) {
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
/*
Think some special features at first
- fixedness -> messness
- messness >= 2 : if swap once, two will be changed
- the number of messness can be {2, 3, 4, ... n}
- so length is always n
- then build permutation, just select one number ,put on 0-th and move others
*/
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << n << '\n';
        for (int m = 1; m <= n; m++) {
            cout << m;
            for (int i = 1; i < m; i++) {
                cout << ' ' << i;
            }
            for (int i = m + 1; i <= n; i++) {
                cout << ' ' << i;
            }
            cout << '\n';
        }
    }
    return 0;
}