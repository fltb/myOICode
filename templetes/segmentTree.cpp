#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
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
class SegmentTree {
    typedef long long ll;
    static const int MAXN = 200000 + 2;
    static const ll DEFAULT = 0;
    struct NodeJS {
        int l, r;
        NodeJS *lson, *rson;
        ll val, lazy;
        NodeJS() : l(0), r(0), lson(nullptr), rson(nullptr), val(DEFAULT), lazy(DEFAULT) {}
        NodeJS(int lc, int rc, NodeJS* ls, NodeJS* rs, ll v) : l(lc), r(rc), lson(ls), rson(rs), val(v), lazy(DEFAULT) {}
        int len() {
            return r - l + 1;
        }
        void pushUp() {
            val = DEFAULT;
            if (lson) {
                val += lson->val;
            }
            if (rson) {
                val += rson->val;
            }
        }
        void pushDown() {
            if (lson) {
                lson->lazy += lazy;
                lson->val += lazy * lson->len();
            }
            if (rson) {
                rson->lazy += lazy;
                rson->val += lazy * rson->len();
            }
            lazy = DEFAULT;
        }
    } nds[MAXN * 2];
    int getMid(int l, int r) {
        return l + ((r - l) >> 1);
    }
    bool inRange(int oil, int oir, NodeJS* nd) {
        return oil <= nd->l && nd->r <= oir;
    }
    void buildTree(ll* arr, int l, int r, int p) {
        if (l == r) {
            nds[p] = NodeJS(l, r, nullptr, nullptr, arr[l]);
            return;
        }
        int m = getMid(l, r);
        buildTree(arr, l, m, p << 1), buildTree(arr, m + 1, r, (p << 1) + 1);
        nds[p] = NodeJS(l, r, &nds[p << 1], &nds[(p << 1) + 1], 0);
        nds[p].pushUp();
    }
    void update(int oil, int oir, ll val, NodeJS* nd) {
        if (nd == nullptr) {
            return;
        }
        if (inRange(oil, oir, nd)) {
            nd->val += nd->len() * val;
            if (nd->l != nd->r) {
                nd->lazy += val;
            }
            return;
        }
        nd->pushDown();
        auto mid = getMid(nd->l, nd->r);
        if (oil <= mid) {
            update(oil, oir, val, nd->lson);
        }
        if (mid < oir) {
            update(oil, oir, val, nd->rson);
        }
        nd->pushUp();
    }
    ll query(int oil, int oir, NodeJS* nd) {
        if (nd == nullptr) {
            return 0;
        }
        if (inRange(oil, oir, nd)) {
            return nd->val;
        }
        nd->pushDown();
        int mid = getMid(nd->l, nd->r);
        ll sum = 0;
        if (oil <= mid) {
            sum += query(oil, oir, nd->lson);
        }
        if (mid < oir) {
            sum += query(oil, oir, nd->rson);
        }
        nd->pushUp();
        return sum;
    }

   public:
    SegmentTree() {}
    void buildTree(ll* arr, int l, int r) {
        buildTree(arr, l, r, 1);
    }
    void update(int oil, int oir, ll val) {
        update(oil, oir, val, &nds[1]);
    }
    ll query(int oil, int oir) {
        return query(oil, oir, &nds[1]);
    }
};
long long a[100000 + 2];
SegmentTree stree;
int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    stree.buildTree(a, 1, n);
    while (m--) {
        int act, l, r;
        cin >> act >> l >> r;
        if (act == 1) {
            int k;
            cin >> k;
            stree.update(l, r, k);
        } else {
            cout << stree.query(l, r) << '\n';
        }
    }
    return 0;
}