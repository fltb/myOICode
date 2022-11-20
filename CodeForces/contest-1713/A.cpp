#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::vector;
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
const int INITAL = 0;
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int mxx = -INITAL, mxy = -INITAL, mnx = INITAL, mny = INITAL;
        while (n--) {
            int x, y;
            cin >> x >> y;
            mxx = max(mxx, x);
            mnx = min(mnx, x);
            mxy = max(mxy, y);
            mny = min(mny, y);
        }
        cout << 2 * (mxx - mnx + mxy - mny) << '\n';
    }
    return 0;
}