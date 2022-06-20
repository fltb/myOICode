#include <ios>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::vector;
template <typename T> inline void read(T& t) {
    int f = 0, c = std::getchar(); t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f) t = -t;
}
template<typename T> inline
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T> inline
T min(T a, T b)
{
    return a < b ? a : b;
}
const int MAXN = 50 + 2;

int main()
{
    std::ios::sync_with_stdio(false);
    
    return 0;
}