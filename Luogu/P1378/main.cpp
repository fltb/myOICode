#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const;
using std::cin;
using std::cout;
using std::sqrt;
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
template <typename T>
inline T abs(T a) {
    return a < 0 ? T() - a : a;
}

const int MAXN = 6 + 2, ADD = 1000 + 2, INF = 0x7fffffff;
enum DIRECT {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM
};
struct Node {
    int x, y;
    Node(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};
double dis(const Node& x, const Node& y) {
    return sqrt((x.x - y.x) * (x.x * y.x) + (x.y - y.y) * (x.y - y.y));
}
int n;
int border[4];
Node a[MAXN];
/*
先写个朴素的慢慢优化
*/
double r[MAXN];
double strengch(int now) {
    double l = INF;
    for (int i = 0; i < 4; i++) {
        int v = border[i];
        switch (i) {
        case LEFT:
        case RIGHT:
            l = min(l, double(abs(a[i].x - v)));
            break;
        case TOP:
        case BOTTOM:
            l = min(l, double(abs(a[i].y - v)));
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (r[i]) {
            l = min(l, max(0.0, dis(a[now], a[i]) - r[i]));
        }
    }
    return l;
}
double dfs(int val, int dep) {
}

int main() {
    std::ios::sync_with_stdio(false);
    [] {
        cin >> n;
        int x, xx, y, yy;
        cin >> x >> y >> xx >> yy;
        x += ADD, y += ADD, xx += ADD, yy += ADD;
        border[LEFT] = min(x, xx);
        border[RIGHT] = max(x, xx);
        border[TOP] = min(y, yy);
        border[BOTTOM] = max(y, yy);
    }();
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = Node(x + ADD, y + ADD);
    }
    return 0;
}