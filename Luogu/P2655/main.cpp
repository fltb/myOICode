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
int month[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int check(int yyyy) {
    if (yyyy % 400 == 0 || (yyyy % 4 == 0 && yyyy % 100 != 0)) {
        month[2] = 29;
        return true;
    }
    month[2] = 28;
    return false;
}
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int bit, yyyy, mm, dd, hh, ss;
        cin >> bit >> yyyy >> mm >> dd >> ss;
        
        long long add = (1 << bit);
    }
    return 0;
}