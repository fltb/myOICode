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
const int MAXN = 60 + 2;
const long long MOD = 998244353;
inline long long qpow(long long a, int p) {
    long long base = a, ans = 1;
    while (p) {
        if (p & 1) {
            ans *= base;
            ans %= MOD;
        }
        base *= base;
        base %= MOD;
        p >>= 1;
    }
    return ans;
}
inline long long inv(long long a) {
    return qpow(a, MOD - 2);
}
/*
Let me guess the situation of Alex wins:
    Alex get the largest number so that he can play it that while Boris can't respond.

啊算了算了不当假洋鬼子了。
看看能不能递推算
假如
    n = 2;
显然
    1 1 0
那么我加上 2 呗；
    n = 4
一共增加了四种情况
- 拿到新加上的两张（以前拿 0）直接赢了
- 拿到增加的一张大的 直接赢了
- 拿到增加一张小的 多一轮! 之前赢了现在就输了 输了同理 平了照样平
- 两张都拿不到，必死
*/
long long J[MAXN];
long long A[MAXN][MAXN], C[MAXN][MAXN];
long long win[MAXN], lose[MAXN];
void initAC();
void genAns();
int main() {
    std::ios::sync_with_stdio(false);
    initAC();
    genAns();
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << win[n] << ' ' << lose[n] << ' ' << 1 << '\n';
    }
    return 0;
}
void initAC() {
    J[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        J[i] = i * J[i - 1] % MOD;
    }
    for (int j = 0; j < MAXN; j++) {
        for (int i = 0; i <= j; i++) {
            // 我菜，我只会逆元求 AC
            A[j][i] = J[j] * inv(J[i]) % MOD;
            C[j][i] = J[j] * inv(J[i]) % MOD * inv(J[j - i]) % MOD;
        }
    }
}
void genAns() {
    win[2] = 1;
    lose[2] = 0;
    for (int i = 4; i < MAXN; i += 2) {
        // 从之前的 i-2 张里面找 i/2-2张 i/2-1, 继承之前拿到的
        win[i] = C[i - 2][i / 2 - 2] + C[i - 2][i / 2 - 1] + lose[i - 2];
        win[i] %= MOD;
        // 继承之前的，或者两个都拿不到
        lose[i] = win[i - 2] + C[i - 2][i / 2];
        lose[i] %= MOD;
    }
}