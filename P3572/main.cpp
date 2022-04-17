#include <iostream>
#include <deque>
#include <algorithm>
using std::cin;
using std::cout;
using std::deque;
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
struct State {
    int val, cur;
    State(int val_=0, int cur_=0) : val(val_), cur(cur_) {}
};
const int MAXN = 1000000 + 2, MAXQ = 25 + 2, MAXH = 1e9 + 2;
int height[MAXN], dp[MAXN], n, q;
int main()
{
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> height[i];
    }
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;
        deque<State> dq;
        dq.push_back(State(0, 1));
        // 第一次做的时候用的贪心，但是贪心其实是错的，会得到太大的值
        for (int i = 2; i <= n; i++)
        {
            // 如果当前的队头已经太小了
            while (!dq.empty() && dq.front().cur + k < i)
            {
                dq.pop_front();
            }
            // 当前最小的肯定是之前最小的跳过来
            auto curBef = dq.front().cur;
            dp[i] = dq.front().val + int(height[i] >= height[curBef]);
            // 当前如果小于或者等于队尾，那么必定不会跳到队尾的点
            while (!dq.empty() 
                    && (dp[i] < dp[dq.back().cur] 
                        || (dp[i] == dp[dq.back().cur] 
                            && height[i] > height[dq.back().cur]
            )))
            {
                dq.pop_back();
            }
            // 当前入队
            dq.push_back(State(dp[i], i));
        }
        cout << dp[n] << "\n";
    }
    return 0;
}