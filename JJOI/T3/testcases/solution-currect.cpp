#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#define cosnt const
using std::cin;
using std::cout;
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
//               0123456
char fname[] = "square1.in";
char fnameO[] = "square1.out";
int main() {
    for (int _ = 1; _ <= 5; _++) {
        fname[6] = _ + '0';
        fnameO[6] = _ + '0';
        std::ifstream is(fname);
        std::ofstream os(fnameO);
        int T;
        is >> T;
        while (T--) {
            int n, ans = 0;
            is >> n;
            for (int fst = 0; fst * fst <= n; fst++) {
                for (int scd = fst; fst * fst + scd * scd <= n; scd++) {
                    for (int thd = scd; thd * thd + scd * scd + fst * fst <= n; thd++) {
                        int fth = std::sqrt(n - fst * fst - scd * scd - thd * thd);
                        if (fth < thd) {
                            break;
                        }
                        if (fth * fth == n - fst * fst - scd * scd - thd * thd) {
                            ans++;
                        }
                    }
                }
            }
            os << ans << '\n';
        }
    }
    return 0;
}