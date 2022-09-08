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
const int MAXN = 100000 + 2;
struct Tower {
    int p, l;
    Tower(int p_=0, int l_=0) : p(p_), l(l_) {}
};
Tower ts[MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    int  n;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int p,l;
        cin >> p >> l;
        ts[i] = Tower(p,l);
    }
    return 0;
}