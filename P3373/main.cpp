#include <iostream>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
typedef long long ll;
const int MAXN = 100000 + 2,
          MOD  = 571373;

struct NodeJS
{
    ll sum,
       l,
       r,
       lasy,
       lson,
       rson;

    NodeJS()
    {
        sum = 0ll;
        l = 0ll;
        r = 0ll;
        lasy = 0ll;
        rson = 0ll;
        lson = 0ll;
    }
};

NodeJS tree[MAXN << 2];

int a[MAXN];

void build(ll cur, ll l, ll r)
{
    NodeJS & now = tree[cur];
    if (l == r)
    {
        now.sum = a[l];
        return;
    }
    
}