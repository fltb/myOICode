#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const;
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
const int mvs[2][8] = {
    {1, 2, +2, +1, -1, -2, -2, -1},
    {2, 1, -1, -2, -2, -1, +1, +2}};
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        // n rows, m cols
        int n, m;
        cin >> n >> m;
        auto inGraph = [&](int x, int y) {
            return (1 <= x) && (x <= n) && (1 <= y) && (y <= m);
        };
        [&]() {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    int f = true;
                    for (int k = 0; k < 8; k++) {
                        if (inGraph(i + mvs[0][k], j + mvs[1][k])) {
                            f = false;
                        }
                    }
                    if (f) {
                        cout << i << ' ' << j << '\n';
                        return;
                    }
                }
            }
            cout << n << ' ' << m << '\n';
        }();
    }
    return 0;
}