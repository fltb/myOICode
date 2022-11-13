#include <algorithm>
#include <cmath>
#include <cstdio>
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
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >>T;
    while(T--){int n, ans = 0;
    cin >> n;
    for (int fst = 0; fst * fst <= n; fst++) {
        for (int scd = fst; fst * fst + scd * scd <= n; scd++) {
            for (int thd = scd; thd * thd + scd * scd + fst * fst <= n; thd++) {
                for (int fth = thd; fth * fth + thd * thd + scd * scd + fst * fst <= n; fth++)  {
                    if (fth * fth + thd * thd + scd * scd + fst * fst == n) {
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans << '\n';}
    return 0;
}