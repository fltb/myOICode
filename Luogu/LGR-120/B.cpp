#include <algorithm>
#include <cstdio>
#include <iomanip>
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
/*
假如 10 门 10000 考生
最大化，所以每个人一个 E。
换句话说
*/
int main() {
    std::ios::sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    cout << std::setprecision(14) << double(b / a) / double(b) << '\n';
    return 0;
}