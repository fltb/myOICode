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
const int MAXN = 100 + 2;
int ds[MAXN];
int rec[MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            rec[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cin >> ds[i];
        }
        bool flag = true;
        rec[0] = ds[0];
        for (int i = 1; i < n; i++) {
            int d = ds[i];
            if (rec[i - 1] - d >= 0 && rec[i - 1] + d >= 0 && rec[i - 1] - d != rec[i - 1] + d) {
                flag = false;
                break;
            } else {
                rec[i] = max(rec[i - 1] + d, rec[i - 1] - d);
            }
        }
        if (flag) {
            for (int i = 0; i < n; i++) {
                cout << rec[i] << ((i == n - 1) ? '\n' : ' ');
            }
        } else {
            cout << -1 << '\n';
        }
    }
    return 0;
}