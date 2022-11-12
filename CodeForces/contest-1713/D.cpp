#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <queue>
#include <vector>
#define cosnt const
using std::cin;
using std::cout;
using std::random_shuffle;
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
交互题，天哪，我写的第一道诶

一个直观的结论就是，一个人赢了几局就停在几层
最高层那个就是赢了的

因为两两对决，形成完全二叉树，层数有限制。恰好为 n + 1 层
一个 vector<int> arr 每次用二分的方式在已知序列当中找，然后如果进去在两个之间就插入，否则忽略
假如 arr.size() == n + 1, 说明最高的那个就是了，Over！

乱序一下数组，防止运气太好。然后逮着开头问就完事了
结果更神奇了（
现在发现好像还有个顺序的单调性，那就不能这么搞了

首先对于同层的，很明显可以通过选取两个 lca 深度 2 的节点比较，来决出这两个子树各自的根
可以做到！那么……
分层，每次消掉最底层，最后就 over 了，正解！
*/
int query(int x, int y) {
    cout << "? " << x << ' ' << y << '\n';
    cout.flush();
    int res;
    cin >> res;
    return res;
}
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> rec[2];
        for (int i = 1; i <= (1 << n); i++) {
            rec[1].push_back(i);
        }
        auto cur = true;
        while (rec[cur].size() > 2)  {
            auto &dc = rec[cur], &dt = rec[!cur];
            cur = !cur;
            dt.clear();
            for (int i = 0; i + 3 < dc.size(); i += 4) {
                auto x1 = dc[i], x3 = dc[i + 2];
                int res = query(x1, x3);
                if (res == 0 || res == 1) {
                    x3 = dc[i + 3];
                }
                if (res == 0 || res == 2) {
                    x1 = dc[i + 1];
                }
                res = query(x1, x3);
                if (res == 2) {
                    x1 = x3;
                }
                dt.push_back(x1);
            }
        }
        auto x = rec[cur][0];
        if (rec[cur].size() > 1) {
            auto y = rec[cur][1];
            if (query(x, y) == 2) {
                x = y;
            }
        }
        cout << "! " << x << '\n';
    }
    return 0;
}