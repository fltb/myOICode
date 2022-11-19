#include <algorithm>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
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
const int MAXN = 10000 + 2;
int a[MAXN];
int main() {
#ifdef FLOATINGBLOCKS
    freopen("harvest.in", "r", stdin);
    freopen("harvest.oo", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (q--) {
        int k;
        cin >> k;
        long long ans = 0;
        __gnu_pbds::priority_queue<int> pq;
        for (int i = 1; i < k; i++) {
            pq.push(a[i]);
        }
        bool act = true;
        for (int i = k; i <= n; i++) {
            pq.push(a[i]);
            if (act) {
                ans += pq.top();
            }
            pq.pop();
            act = !act;
        }
        while (!pq.empty()) {
            if (act) {
                ans += pq.top();
            }
            pq.pop();
            act = !act;
        }
        cout << ans << '\n';
    }
    return 0;
}