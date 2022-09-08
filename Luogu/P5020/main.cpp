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
// 写个埃氏筛
const int MAXA = 25000 + 2, MAXN = 100 + 2;
int numbers[MAXN];
bool Eratosthenes[MAXA];
int main() {
    std::ios::sync_with_stdio(false);
    auto init = [](int mxa) {
        for (int i = 0; i < mxa; i++) {
            Eratosthenes[i] = false;
        }
    };
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> numbers[i];
        }
        std::sort(&numbers[0], &numbers[n]);
        int mxa = numbers[n - 1] + 1;
        init(mxa);
        int m = 0;
        for (int i = 0; i < n; i++) {
            int a = numbers[i];
            if (!Eratosthenes[a]) {
                m++;
                Eratosthenes[a] = true;
                for (int j = a; j < mxa; j++) {
                    if (Eratosthenes[j - a]) {
                        Eratosthenes[j] = true;
                    }
                }
            }
        }
        cout << m << '\n';
    }

    return 0;
}