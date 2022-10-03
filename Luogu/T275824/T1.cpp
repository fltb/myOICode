#include <algorithm>
#include <iostream>
using std::cin;
using std::cout;
typedef long long ll;
const int MAXN = 100000 + 2,
          MAXT = 1 << 30;
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
struct Node {
    ll id,
        l,
        r,
        time,
        lasy_tag,
        lson,
        rson;
    Node() {
        id = 0;
        l = 0;
        r = 0;
        time = 1;
        lasy_tag = 1;
        lson = 0;
        rson = 0;
    }
    Node(ll cur, ll le, ll rr) {
        *this = Node();
        id = cur;
        l = le;
        r = rr;
    }
    void push_up_time();
    void push_down_time();
};

Node tree[MAXN << 2];

void Node::push_up_time() {
    time = tree[lson].time * tree[rson].time;
}

void Node::push_down_time() {
    Node& ls = tree[lson];
    Node& rs = tree[rson];

    ls.lasy_tag *= lasy_tag;
    ls.time = ls.time * lasy_tag * (ls.r - ls.l + 1);

    rs.lasy_tag *= lasy_tag;
    rs.time = rs.time * lasy_tag * (rs.r - rs.l + 1);

    lasy_tag = 1;
}

ll cnt_tree = 1, a[MAXN];

void build(ll cur, ll l, ll r) {
    Node& now = tree[cur];
    now = Node(cur, l, r);
    if (l == r)  // is leaf
    {
        now.time = a[l];
        return;
    }
    ll mid = (l + r) / 2;
    now.lson = ++cnt_tree;
    build(cnt_tree, l, mid);
    now.rson = ++cnt_tree;
    build(cnt_tree, mid + 1, r);

    now.push_up_time();
}

void update(ll cur, ll original_l, ll original_r, ll val) {
    Node& now = tree[cur];
    if (original_l <= now.l && original_r >= now.r) {
        now.time *= val * (now.r - now.l + 1);
        if (now.l != now.r) {
            now.lasy_tag *= val;
        }
        return;
    }
    now.push_down_time();
    ll mid = (now.l + now.r) / 2;
    if (original_l <= mid) {
        update(now.lson, original_l, original_r, val);
    }
    if (original_r > mid) {
        update(now.rson, original_l, original_r, val);
    }
    now.push_up_time();
}

ll query(ll cur, ll original_l, ll original_r) {
    if (cur == 0) {
        return 0;
    }
    Node& now = tree[cur];
    if (original_l <= now.l && original_r >= now.r) {
        return now.time;
    }
    now.push_down_time();
    ll mid = (now.l + now.r) / 2;
    ll time = 1;
    if (original_l <= mid) {
        time *= query(now.lson, original_l, original_r);
    }
    if (original_r > mid) {
        time *= query(now.rson, original_l, original_r);
    }
    return time;
}
const int MAXNN = 5000 + 2, LIMIT = 1 << 30;
ll FFNUM = 0x7fffffff;
ll dp[MAXNN][MAXNN];
int main() {
    std::ios::sync_with_stdio(false);
    ll n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        dp[i][i] = a[i];
    }

    for (int i = 0; i < m; ++i) {
        int md;
        cin >> md;
        if (md == 1) {
            ll x, y;
            cin >> x >> y;
            a[x] = y;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    dp[i][j] = (j == i) ? a[i] : 1;
                }
            }
        } else if (md == 2) {
            ll x, y;
            cin >> x >> y;
            auto re = [&]() {
                for (int len = 2; len <= y - x + 1; len++) {
                    for (int i = x; i + len - 1 <= y; i++) {
                        int j = i + len - 1;
                        dp[i][j] = max(max(a[i], a[j]), max(dp[i][j - 1], dp[i][j - 1] * a[j]));
                        if (dp[i][j] > LIMIT) {
                            return FFNUM;
                        }
                    }
                }
                return dp[x][y];
            }();
            if (re != FFNUM) {
                cout << max(1ll, re) << '\n';
            } else {
                cout << "Too large\n";
            }
        } else {
            cout << "FUCKCCF!!!"
                 << "禁赛一年!!!"
                 << '\n';
            ;
            exit(1);
        }
    }
    return 0;
}