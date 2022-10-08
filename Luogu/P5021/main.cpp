#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <set>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::multiset;
using std::vector;
template <typename T>
inline void read(T& t) {
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
/*
二分答案，然后一个check
*/
struct Edge {
    int u, v, c;
    Edge(int a = 0, int b = 0, int x = 0) : u(a), v(b), c(x) {}
    int to(int x) { return x == u ? v : u; }
};
const int MAXN = 50000 + 5, indefinty = 0x3f3f3f3f;
int n, m;
vector<Edge> es;
vector<int> graph[MAXN];
// 板子完了，重头戏来了
namespace chk {
int limit, ans;
/*
我们现在开始遍历这个树，然后观察它是否可以符合这个要求

具体点好了。我进行尝试。
先暴力：
    我穷举每个节点，看看能不能走出一条边。如果不行就回退
    一个显然可行的贪心是，我们如果从叶子开始走，那就不会影响到别人，回退操作就没有了
    对于每个节点，我们选取自链当中最长的一条或者两条
        va >= k ans++ pop(a)
        va + vb >= k ans++ pop(a) pop(b)
    最后判断那个 ans 是不是 >= m
*/
int dfs(int x, int fa) {
    multiset<int> ms;
    for (auto ei : graph[x]) {
        auto to = es[ei].to(x);
        if (to != fa) {
            auto v = dfs(to, x) + es[ei].c;
            if (v >= limit) {
                ++ans;
            } else {
                ms.insert(v);
            }
        }
    }
    int mx = 0;
    while (ms.size() > 1) {
        auto be = *ms.begin();
        auto it = ms.lower_bound(limit - be);
        if (it == ms.begin() && ms.count(*it) & 1) { 
            ++it; // 找到自己
        }
        if (it == ms.end()) {
            mx = max(mx, *ms.begin());
            ms.erase((ms.begin()));
        } else {
            ++ans;
            ms.erase(it);
            ms.erase(ms.begin());
        }
    }
    if (ms.size() == 1) {
        return max(mx, *ms.begin());
    } else {
        return mx;
    }
}
bool check() {
    ans = 0;
    dfs(1, -1);
    return ans >= m;
}
}  // namespace chk
int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    int l = indefinty, r = 0;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        es.push_back(Edge(a, b, c));
        graph[a].push_back(es.size() - 1);
        graph[b].push_back((es.size() - 1));
        l = min(l, c);
        r += c;
    }
    int ans = l;
    while (l <= r) {
        chk::limit = (r + l) / 2;
        if (chk::check()) {
            ans = chk::limit;
            l = chk::limit + 1;
        } else {
            r = chk::limit - 1;
        }
    }
    cout << ans << '\n';
    return 0;
}