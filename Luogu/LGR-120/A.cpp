#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>
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

int main() {
    std::ios::sync_with_stdio(false);
    int n, cnt=0;
    cin >> n;
    cin.get();
    while (n--) {
        std::string s;
        std::getline(cin, s);
        auto fstUJ = s.find_first_not_of("# ");
        auto fstJ = s.find_first_of("#");
        if (fstJ == std::string::npos || fstJ + 1 == s.size()) { // no # or no after
            continue;
        }
        if (fstUJ != std::string::npos && fstUJ < fstJ) { // befor # has charactor
            continue;
        }
        auto atfS = s[fstJ+1] == ' ';
        if (!atfS) { // no space after
            continue;
        }
        auto aftJ = s.find_first_not_of(" ", fstJ+1);
        if (aftJ != std::string::npos) { // has after
            cnt++;
        }
    }
    cout << cnt << '\n';
    return 0;
}