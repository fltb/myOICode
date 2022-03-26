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
    int Sum[MAXN][MAXN], Tan[MAXN], cur=1;
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
        for (int i = 1; i <= cur; i++)
        {
            Sum[i][cur] = Sum[i][cur-1] + int(st.size() - i <= 1);
            # ifdef FLOATINGBLOCKS
            cout << "Sum " << i << " " << cur << " " << Sum[i][cur] << "\n";
            # endif
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
        cout << my.Sum[l][r] << "\n";
    }
    return 0;
}
