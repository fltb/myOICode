#include <iostream>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
typedef unsigned long long ull;
const int MAXN = 100000 + 2;

struct Node
{
    ull id,
        l,
        r,
        sum,
        lasy_tag,
        lson,
        rson;
    Node()
    {
        id = 0;
        l = 0;
        r = 0;
        sum = 0;
        lasy_tag = 0;
        lson = 0;
        rson = 0;
    }
    Node(ull cur, ull ll, ull rr)
    {
        *this = Node();
        id = cur;
        l = ll;
        r = rr;
    }
    void push_up_sum();
    void push_down_sum();
};

Node tree[MAXN<<2];

void Node::push_up_sum()
{
    sum = tree[lson].sum + tree[rson].sum;
}

void Node::push_down_sum()
{
    Node & ls = tree[lson];
    Node & rs = tree[rson];

    ls.lasy_tag += lasy_tag;
    ls.sum = ls.sum + lasy_tag * (ls.r - ls.l + 1);

    rs.lasy_tag += lasy_tag;
    rs.sum = rs.sum + lasy_tag * (rs.r - rs.l + 1);

    lasy_tag = 0;
}

ull cnt_tree = 1, a[MAXN];

void build(ull cur, ull l, ull r)
{
    Node & now = tree[cur];
    now = Node(cur, l, r);
    if (l == r) // is leave
    {
        now.sum = a[l];
        return;
    }
    ull mid = (l + r) / 2;
    now.lson = ++cnt_tree;
    build(cnt_tree, l, mid);
    now.rson = ++cnt_tree;
    build(cnt_tree, mid + 1, r);
    
    now.push_up_sum();
}

void update(ull cur, ull original_l, ull original_r, ull val)
{
    Node & now = tree[cur];
    if (original_l <= now.l && original_r >= now.r)
    {
        now.sum += val * (now.r - now.l + 1);
        if (now.l != now.r)
        {
            now.lasy_tag += val;
        }
        return;
    }
    now.push_down_sum();
    ull mid = (now.l + now.r) / 2;
    if (original_l <= mid)
    {
        update(now.lson, original_l, original_r, val);
    }
    if (original_r > mid)
    {
        update(now.rson, original_l, original_r, val);
    }
    now.push_up_sum();
}

ull query(ull cur, ull original_l, ull original_r)
{
    if (cur == 0)
    {
        return 0;
    }
    Node & now = tree[cur];
    if (original_l <= now.l && original_r >= now.r)
    {
        return now.sum;
    }
    now.push_down_sum();
    ull mid = (now.l + now.r) / 2;
    ull sum = 0;
    if (original_l <= mid)
    {
        sum += query(now.lson, original_l, original_r);
    }
    if (original_r > mid)
    {
        sum += query(now.rson, original_l, original_r);
    }
    return sum;
}


int main()
{
    std::ios::sync_with_stdio (false);
    ull n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }

    build(1, 1, n);

    for (int i = 0; i < m; ++i)
    {
        int md;
        cin >> md;
        if (md == 1)
        {
            ull x, y, k;
            cin >> x >> y >> k;
            update(1, x, y, k);
        }
        else if (md == 2)
        {
            ull x, y;
            cin >> x >> y;
            cout << query(1, x, y) << endl;
        }
        else
        {
            cout << "FUCKCCF!!!"
                 << "禁赛一年!!!"
                 << endl;;
            exit(1);
        }
    }
    return 0;
}