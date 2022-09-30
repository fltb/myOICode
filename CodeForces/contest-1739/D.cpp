#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::get;
using std::tuple;
using std::unordered_map;
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
const int MAXN = 2 * 1e5 + 2;
/*
Do step 1 and 2 really make sence? Confused.
Consider 3 only.

record all depth of n nodes, sort it.
Can prove if all node of *maxd* linked root, the maxd will = (maxd + 1) / 2.

cout current maxd when k == 0;

WRONG...

try binary search depth and calculate the steps
*/

// depth to cnt of nodes
vector<int> graph[MAXN];
int maxd = 0;
void dfsD(int x, int d) {
    maxd = max(maxd, d);
    for (auto to : graph[x]) {
        dfsD(to, d + 1);
    }
}
int limit;
// return <depth, cnt>
tuple<int, int> dfsA(int x) {
    int depth = 0, cnt = 0;
    for (auto to : graph[x]) {
        auto res = dfsA(to);
        cnt += get<1>(res);
        // find subtree that depth >= limit, link here to root if now is not root
        if (get<0>(res) >= limit && x != 1) {
            cnt++;
        } else {  // add depth
            depth = max(depth, get<0>(res));
        }
    }
    return tuple<int, int>(depth + 1, cnt);
}
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i <= n; i++) {
            graph[i].clear();
        }
        for (int i = 2; i <= n; i++) {
            int fa;
            cin >> fa;
            graph[fa].push_back(i);
        }
        maxd = 0;
        dfsD(1, 0);
        // 二分答案吧
        int l = 1, r = n - 1, ans = maxd;
        while (l <= r) {
            limit = (l + r) / 2;
            int steps = get<1>(dfsA(1));
            if (steps > k) {
                l = limit + 1;
            } else {
                r = limit - 1;
                ans = limit;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}