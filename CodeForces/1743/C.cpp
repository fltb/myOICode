#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const
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
template <typename T>
inline T update(T& a, T b) {
    return a = max(a, b);
}
const int MAXN = 2e5 + 4;
bool has[MAXN];
int num[MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cin.get();
        for (int i = 1; i <= n; i++) {
            char ch;
            cin >> ch;
            has[i] = ch == '1';
        }
        for (int i = 1; i <= n; i++) {
            cin >> num[i];
        }
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            auto mn = num[i], sm = num[i];
            auto j = i + 1;
            while (j <= n && has[j]) {
                mn = min(mn, num[j]);
                sm += num[j];
                j++;
            }
            ans += sm - mn;
            i = j - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}