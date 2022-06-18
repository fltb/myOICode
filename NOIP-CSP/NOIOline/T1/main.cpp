#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using std::cin;
using std::cout;
template<typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

# ifndef FLOATINGBLOCKS
const int MAXN = 1e4 + 10;
# endif
# ifdef FLOATINGBLOCKS
const int MAXN = 12;
# endif

struct NodeJS {
    int a, b;
    NodeJS(int a_=0, int b_=0) : a(a_), b(b_) {}
    bool operator<(const NodeJS & x) const
    {
        if (a == x.a)
        {
            return false;
        }
        else
        {
            return b < x.b;
        }
    }
    bool operator==(const NodeJS & x) const
    {
        return (a == x.a && b == x.b);
    }
    bool operator>(const NodeJS & x) const
    {
        return !((*this) < x || (*this) == x);
    }
};

class DStack{
public:
    std::stack<NodeJS> st;
    std::vector<int> Sum[MAXN];
    int cur=1, start[MAXN];
    void mypush(const NodeJS & item)
    {
        if (st.empty() || item < st.top())
        {
            st.push(item);
        }
        else
        {
            while (!st.empty() && !(item < st.top()))
            {
                st.pop();
            }
            st.push(item);
        }
        start[cur] = st.size();
        for (int i = 1; i <= cur; i++)
        {
            if (st.size() <= start[i])
            {
                // update
                Sum[i].push_back(cur);   
            }
        }
        cur++;
    }
};

int n, q, tmp[MAXN];
DStack my;
int main()
{
    std::freopen("stack.in", "r", stdin);
    std::freopen("stack.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> tmp[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int now;
        cin >> now;
        my.mypush(NodeJS(tmp[i], now));
    }
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        auto & sum = my.Sum[l];
        auto it = std::upper_bound(sum.begin(), sum.end(), r);
        auto ans = 0;
        ans += it - sum.begin();
        cout << "    FND " << *it << " NOW " << l << " " << r << "\n";
        cout << ans << "\n";
    }
    return 0;
}
