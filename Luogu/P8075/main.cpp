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
const int MAXN = 4000 + 5;
struct Rec {
    int c[MAXN],
        r[MAXN];
    int tot;
    void add(int x, int y) {
        c[x + 2001]++, r[y + 2001]++, tot++;
    }
};
Rec S, M;
int n, m;
long long getV(int a[], int lim, int tot) {
    long long res = 0;
    int x1 = 1, x2 = 1, add = 1;
    while (x1 <= lim && a[x1] < 1) {
        x1++;
    }
    add = a[x1];
    x2 = x1 + 1;
    while (true) {
        while (x2 <= lim && a[x2] < 1) {
            x2++;
        }
        if (x2 > lim) {
            break;
        }
        res += (long long)add * (tot - add) * (x2 - x1);
        add += a[x2];
        x1 = x2++;
    }
    return res;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            if (ch == 'S') {
                S.add(i + j, i - j);
            } else if (ch == 'M') {
                M.add(i + j, i - j);
            }
        }
    }
    cout << (getV(M.c, 4003, M.tot) + getV(M.r, 4003, M.tot)) / 2 << ' '
         << (getV(S.c, 4003, S.tot) + getV(S.r, 4003, S.tot)) / 2 << '\n';
    return 0;
}