#include <cstddef>
#include <deque>
#include <iostream>
#include <queue>
#include <algorithm>
using std::cin;
using std::cout;
using std::deque;
using std::sort;
template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
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
const int MAXSPEED = 1e6 + 2, MAXN = 1000 + 2;
struct NodeJS {
    int place, val;
    NodeJS(int p=0, int v=0) : place(p), val(v) {}
    bool operator<(const NodeJS & x) const
    {
        return place < x.place;
    }
};
struct State {
    NodeJS * nd;
    int cnt;
    State(NodeJS * nodePtr=nullptr, int cnt_=0) : nd(nodePtr), cnt(cnt_) {}
};
int n;
deque<State> dp[MAXN];
NodeJS nodes[MAXN];
int solve()
{
    int ans = 0;
    // clear
    for (int i = 0; i < MAXN; i++)
    {
        dp[i] = deque<State>();
    }

    for (int i = 1; i <= n; i++)
    {
        auto & now = nodes[i];
        auto & dpnow = dp[i];
        dpnow.push_back(State(&now, now.val));
        ans = max(ans, now.val);
        for (int j = i - 1; j >= 1; j--)
        {
            auto & pre = nodes[j];
            auto & dppre = dp[j];
            State add;
            while (!dppre.empty() && !(now.place - pre.place < pre.place - dppre.front().nd->place))
            {
                add = dppre.front();
                dppre.pop_front();
            }
            if (dpnow.back().cnt < add.cnt + now.val)
            {
                dpnow.push_back(State(&pre, add.cnt + now.val));
                ans = max(ans, add.cnt + now.val);
            }
            if (add.nd != nullptr)
            {
                dppre.push_front(add);
            }
        }
    }
    return ans;
}
int main()
{
    
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int p, v;
        cin >> p >> v;
        nodes[i] = NodeJS(p, v);
    }

    sort(&nodes[1], &nodes[n+1]);

    int ans = solve();

    for (int i = 1; i <= n; i++)
    {
        nodes[i].place = MAXSPEED - nodes[i].place + 1;
    }
    sort(&nodes[1], &nodes[n+1]);

    ans = max(ans, solve());

    cout << ans << "\n";
    return 0;
}
