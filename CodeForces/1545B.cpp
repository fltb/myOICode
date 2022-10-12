#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::vector;
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
const int MAXN = 1e5 + 2, MOD = 998244353;
int qpow(int a, int p) {
    int res = 1, base = a;
    while (p) {
        if (p & 1) {
            res = (long long)res * base % MOD;
        }
        p >>= 1;
        base = (long long)base * base % MOD;
    }
    return res;
}
int inv(int a) {
    return qpow(a, MOD - 2);
}
int F[MAXN];
void init() {
    F[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        F[i] = (long long)F[i - 1] * i % MOD;
    }
}
int C(int n, int m) {
    return (long long)F[n] * inv(F[m]) % MOD * inv(F[n - m]) % MOD;
}
char st[MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    init();
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        cin.get();
        cin.getline(st, MAXN);
        int cnt11 = 0, cnt0 = 0;
        for (int i = 0; i < n; i++) {
            if (st[i] == '1' && st[i] == st[i + 1]) {
                cnt11++;
                i++;
            } else if (st[i] == '0') {
                cnt0++;
            }
        }
        cout << C(cnt11 + cnt0, cnt0) << '\n';
    }
    return 0;
}