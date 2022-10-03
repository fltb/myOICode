#include <bits/types/struct_tm.h>
#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const;
using std::cin;
using std::cout;
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
const int MAXN = 200000 + 5;
int a[MAXN], n, rooted[MAXN], root;
int vis[MAXN], tme;
void dfs(int x) {
    vis[x] = tme;
    if (a[x] == x) { // 我是自环
        if (root) {
            rooted[x] = root; // 你不是
        } else {
            root = x; // 你是根！
        }
        return;
    } else if (vis[rooted[x]] == tme) {
        if (root) {
            rooted[x] = root;
        } else {
            root = x;
            rooted[x] = x;
        }
    } else if (!vis[rooted[x]]) {
        dfs(rooted[x]);
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rooted[i] = a[i];
        if (a[i] == i) {
            root = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ++tme;
            dfs(i);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += a[i] != rooted[i];
    }
    cout << cnt << '\n';
    for (int i = 1; i <= n; i++) {
        cout << rooted[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}