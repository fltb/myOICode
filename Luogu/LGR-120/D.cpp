#include <algorithm>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
#include <queue>
#define cosnt const;
using std::cin;
using std::cout;
using std::vector;
using std::queue;
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
const int MAXN = 300000 + 2;
struct Edge {
    int u, v, c;
    int dir;
    Edge(int u_ = 0, int v_ = 0, int c_ = 0) : u(u_), v(v_), c(c_), dir(0) {}
    int to(int from) {
        return from == u ? v : u;
    }
    void setD(int from) {
        dir = from == u ? 1 : 2;
    }
    void setDR(int from) {
        dir = from == u ? 2 : 1;
    }
    void clsD() {
        dir = 0;
    }
};
int n, s, t;
Edge es[MAXN];
vector<int> nd[MAXN];
/*
    既然是一棵树，那么只要去掉一个边就可以把树变成两个不相连的部分了
    每条边被加上去的时候，都是会把经过它的每个节点的数量与权相乘
    好像算不出来
    那树形 DP 呢？上条边接上，这条边砍掉？
    那么下一个集合丢掉一个点，上一个集合加上一个点，好像是可以用 O1 算出来的
    那么我先初始化两个集合好了。第一步 s 的集合是 {} , t 是 {all}？好像不行，因为如果是一条链那事情就很好玩了。
    so？ 第一个 dfs 从 t 开始，容纳最多的点，剩下的丢给 s。
    从那个刚刚好分开的边，也就是紧连着 s 的那条边，开始 dp，给那个边的 dp 赋值 sum
    接着 DP 过程，一个一个“叛逃”
    dp[x] = dp[fa] - 对老集合的贡献 + 对新集合的贡献;
                       TtoN           StoN
    如果当前的小于出现过的最小值，把状态也记录下来
    dp[], TtoN[], StoN[]
    Over!

    ADD：
    好像那个“叛逃”的思路不太行，那换一个思路，记录经过每条边去 S 和 T 的流量，然后把总流量减去这条边的流量
    找到最小的那条边之后再进行建树的操作，如何？
*/
int dp[MAXN], TtoN[MAXN], StoN[MAXN], state[MAXN];
long long sum = 0;
void dfsD(int x, int fa, std::function<void(int, int, int)> run) {
    for (auto id : nd[x]) {
        auto& e = es[id];
        auto to = e.to(x);
        if (to != fa) {
            run(to, x, e.c);
            dfsD(to, x, run);
        }
    }
}
void dfsT() {
    dfsD(t, -1, std::function<void(int, int, int)>([](int x, int fa, int dis) {
             TtoN[x] = dis + TtoN[fa];
         }));
}
void dfsS() {
    dfsD(s, -1, std::function<void(int, int, int)>([](int x, int fa, int dis) {
             StoN[x] = dis + StoN[fa];
         }));
}
void recState() {
    for (int i = 1; i <= n; i++) {
        state[i] = es[i].dir;
    }
}
// 现在形成一个初始的状态
int iniEdge = 0;
void dfsIniT(int x, int fa) {
    for (auto id : nd[x]) {
        auto& e = es[id];
        auto to = e.to(x);
        if (to == s) {
            iniEdge = id;
            continue;
        }
        if (to != fa) {
            e.setD(x);
            sum += TtoN[to];
            dfsIniT(to, x);
        }
    }
}
void dfsIniS(int x, int fa) {
    for (auto id : nd[x]) {
        auto& e = es[id];
        auto to = e.to(x);
        if (to != fa && id != iniEdge) {
            e.setD(x);
            sum += StoN[to];
            dfsIniS(to, x);
        }
    }
}
void Init() {
    dfsT();
    dfsS();
    dfsIniT(t, -1);
    dfsIniS(s, -1);
    recState();
    dp[s] = sum;
}
// 最后进行求解
void bfsDP() {
    queue<std::pair<int,int>>q;
    q.push(std::make_pair(es[iniEdge].to(s), iniEdge));
    while (!q.empty()) {
        auto x = q.front().first, fe = q.front().second;
        q.pop();
        // 现在开始“叛逃”
        dp[x] = dp[es[fe].to(x)] + StoN[x] - TtoN[x];
        es[fe].setDR(x);
        if (dp[x] < sum) {
            sum = dp[x];
            recState();
        }
        for (auto id : nd[x]){
            auto& e = es[id];
            if (id != fe && e.to(x) != t) {
                q.push(std::make_pair(e.to(x), id));
            }
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> s >> t;
    for (int i = 1; i < n; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        es[i] = Edge(u, v, c);
        nd[u].push_back(i);
        nd[v].push_back(i);
    }
    Init();
    bfsDP();
    cout << sum << '\n';
    for (int i = 1; i < n; i++) {
        cout << state[i];
    }
    cout << '\n';
    return 0;
}