#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
using std::cin;
using std::cout;
using std::lower_bound;
using std::sort;
using std::sqrt;
template <typename T>
inline T min(const T& a, const T& b) {
    return a < b ? a : b;
}
template <typename T>
inline T max(const T& a, const T& b) {
    return a < b ? b : a;
}
const int MAXN = 1e6 + 2,
          MAXBLOCK = 1e3 + 2;
int origin[MAXN], sorted[MAXN];
int tot, sz;
inline int belong(int i) {
    return (i - 1) / sz;
}
inline int blb(int i) {
    return i * sz + 1;
}
inline int brb(int i) {
    return (i + 1) * sz;
}
struct Block {
    int l, r, lazy;
    Block() : l(0), r(0), lazy(0) {}
    Block(int ll, int rr) : l(ll), r(rr) {
        for (int i = l; i <= r; i++) {
            sorted[i] = origin[i];
        }
        sort(&sorted[l], &sorted[r + 1]);
    }
    void add(int from, int to, int w) {
        if (from == l && to == r) {
            lazy += w;
        } else {
            for (int i = from; i <= to; i++) {
                origin[i] += w;
            }
            for (int i = l; i <= r; i++) {
                origin[i] += lazy;
                sorted[i] = origin[i];
            }
            lazy = 0;
            sort(&sorted[l], &sorted[r + 1]);
        }
    }
    int fnd(int from, int to, int c) {
        c -= lazy;
        if (from == l && to == r) {
            auto it = lower_bound(&sorted[l], &sorted[r + 1], c);
            return (r - l + 1) - (it - &sorted[l]);
        } else {
            int ans = 0;
            for (int i = from; i <= to; i++) {
                ans += int(c <= origin[i]);
            }
            return ans;
        }
    }
} fltb[MAXBLOCK];
inline void init(int n) {
    sz = sqrt(n) + 2;
    tot = n / sz + int(bool(n % sz));
    for (int i = 0; i < tot; i++) {
        fltb[i] = Block(blb(i), min(brb(i), n));
    }
}
inline void add(int l, int r, int k) {
    auto bl = belong(l), br = belong(r);
    for (int i = bl; i <= br; i++) {
        fltb[i].add(max(l, blb(i)), min(r, brb(i)), k);
    }
}
inline int ck(int l, int r, int c) {
    auto bl = belong(l), br = belong(r);
    int ans = 0;
    for (int i = bl; i <= br; i++) {
        ans += fltb[i].fnd(max(l, blb(i)), min(r, brb(i)), c);
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> origin[i];
    }
    init(n);
    while (q--) {
        int l, r, v;
        char md;
        cin.get();
        cin >> md;
        cin >> l >> r >> v;
        if (md == 'M') {
            add(l, r, v);
        } else {
            cout << ck(l, r, v) << '\n';
        }
    }
}