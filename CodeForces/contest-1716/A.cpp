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
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n < 6) {
            switch (n) {
            case 1:
            case 4:
            case 5:
                cout << 2;
                break;
            case 2:
            case 3:
                cout << 1;
                break;
            }
        } else {
            auto ans = (n / 6) * 2;
            switch (n % 6) {
            case 1:
            case 2:
            case 3:
                ans += 1;
                break;
            case 4:
            case 5:
                ans += 2;
            }
            cout << ans;
        }
        cout << '\n';
    }
    return 0;
}