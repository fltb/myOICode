#include <deque>
#include <iostream>
#include <cstdio>
#include <ostream>
#include <queue>
#include <algorithm>
using std::cin;
using std::cout;
using std::deque;
template <typename T> inline void read(T& t) {
    int f = 0, c = std::getchar(); t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f) t = -t;
}
template<typename T> inline
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T> inline
T min(T a, T b)
{
    return a < b ? a : b;
}
struct NodeJS {
    int l, r;
    NodeJS(int l_=0, int r_=0) : l(l_), r(r_) {}
};
struct State {
    NodeJS nd;
    int pre;
    State(const NodeJS & nd_, int pre_) : nd(nd_), pre(pre_){}
};
int main()
{
    int n, ans = 0;
    read(n);
    deque<State> dq;
    for (int i = 0; i < n; i++)
    {
        NodeJS now;
        read(now.l);
        read(now.r);
        while (!dq.empty() && dq.front().nd.l > now.r)
        {
            dq.pop_front();
        }
        int len = 1;
        if (!dq.empty())
        {
            len = i - dq.front().pre + 1;
        }
        ans = max(ans, len);
        int tmp = i;
        while (!dq.empty() && dq.back().nd.l < now.l)
        {
            tmp = dq.back().pre;
            dq.pop_back();
        }
        dq.push_back(State(now, tmp));
    }
    cout << ans << "\n";
    return 0;
}