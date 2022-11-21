#include <algorithm>
#include <cmath>
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
struct SplitedArray {
   private:
    static const int MAXN = 1e6 + 2;
    static const int MAXBLOCK = 1e3 + 2;
    int origin[MAXN], sorted[MAXN];
    int bsz, btot;
    struct Block {
        int *sorted, *origin;
        int l, r, lazy;
        Block() : sorted(0), origin(0), l(0), r(0), lazy(0) {}
        Block(int* st, int* ori, int ll, int rr) : sorted(st), origin(ori), l(ll), r(rr), lazy(0) {
            for (int i = l; i <= r; i++) {
                sorted[i] = origin[i];
            }
            std::sort(&sorted[l], &sorted[r + 1]);
        }
        int findGreater(int from, int to, int c) {
            c -= lazy;
            if (from == l && to == r) {
                auto it = std::lower_bound(&sorted[l], &sorted[r + 1], c);
                return (r - l + 1) - int(it - &sorted[l]);
            } else {
                int ans = 0;
                for (int i = from; i <= to; i++) {
                    ans += int(origin[i] >= c);
                }
                return ans;
            }
        }
        void add(int from, int to, int w) {
            if (from == l && to == r) {
                lazy += w;
                return;
            }
            for (int i = from; i <= to; i++) {
                origin[i] += w;
            }
            for (int i = l; i <= r; i++) {
                origin[i] += lazy;
                sorted[i] = origin[i];
            }
            lazy = 0;
            std::sort(&sorted[l], &sorted[r + 1]);
        }
        void addLeft(int rr, int w) {
            add(l, rr, w);
        }
        void addRight(int ll, int w) {
            add(ll, r, w);
        }
    };
    Block floatingblocks[MAXBLOCK];
    int belongBlock(int i) {
        return (i - 1) / bsz;
    }
    int getbl(int i) {
        return i * bsz + 1;
    }
    int getbr(int i) {
        return (i + 1) * bsz;
    }

   public:
    SplitedArray() {}
    void init(int n) {
        bsz = std::sqrt(n) + 2;
        btot = n / bsz + bool(n % bsz);
        for (int i = 1; i <= n; i++) {
            cin >> origin[i];
        }
        for (int i = 0; i < btot; i++) {
            floatingblocks[i] = Block(sorted, origin, getbl(i), min(n, getbr(i)));
        }
    }
    void add(int l, int r, int w) {
        int bl = belongBlock(l), br = belongBlock(r);
        for (int i = bl; i <= br; i++) {
            floatingblocks[i].add(max(l, getbl(i)), min(r, getbr(i)), w);
        }
    }
    int srh(int l, int r, int c) {
        int bl = belongBlock(l), br = belongBlock(r);
        int ans = 0;
        for (int i = bl; i <= br; i++) {
            ans += floatingblocks[i].findGreater(max(l, getbl(i)), min(r, getbr(i)), c);
        }
        return ans;
    }
} solver;
int main() {
    std::ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    solver.init(n);
    while (q--) {
        char ch;
        cin.get();
        cin >> ch;
        if (ch == 'M') {
            int l, r, k;
            cin >> l >> r >> k;
            solver.add(l, r, k);
        } else {
            int l, r, c;
            cin >> l >> r >> c;
            cout << solver.srh(l, r, c) << '\n';
        }
    }
    return 0;
}