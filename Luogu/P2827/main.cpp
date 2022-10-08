#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <queue>
#define cosnt const;
using std::cin;
using std::cout;
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
int q;
struct Bug {
    long long iniL;
    Bug(long long len, long long time) : iniL(len - time * q) {}
    bool operator<(const Bug& x) const {
        return iniL < x.iniL;
    }
    long long getL(int t) const {
        return iniL + t * q;
    }
};
const int MAXN = 100000 + 2, INF = 0x3fffffff;
int iniBugs[MAXN];
int main() {
    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;
    ::q = q;
    for (int i = 0; i < n; ++i) {
        cin >> iniBugs[i];
    }
    std::sort(&iniBugs[0], &iniBugs[n]);
    queue<Bug> qs[3];
    for (int i = n-1; i >= 0; i--) {
        qs[0].push(Bug(iniBugs[i], 0));
    }
    int ck = 1;
    auto cbug = [&qs]() {
        auto bug = Bug(-INF, 0);
        auto chosen = 0;
        for (int j = 0; j < 3; j++) {
            if (!qs[j].empty() && bug.iniL < qs[j].front().iniL) {
                bug = qs[j].front();
                chosen = j;
            }
        }
        qs[chosen].pop();
        return bug; 
    };
    auto going = [&qs]() {
        for (int j = 0; j < 3; j++) {
            if (!qs[j].empty()) {
                return true;
            }
        }
        return false;
    };
    for (int i = 1; i <= m; ++i) {
        auto bug = cbug();
        if (ck == t) {
            cout << bug.getL(i - 1) << ' ';
            ck = 0;
        }
        auto l = (long long)bug.getL(i - 1) * u / v;
        auto r = bug.getL(i - 1) - l;
        qs[1].push(Bug(l, i));
        qs[2].push(Bug(r, i));
        ++ck;
    }
    cout << '\n';
    int tt = 1;
    while (going()) {
        auto bug = cbug();
        if (tt == t) {
            cout << bug.getL(m) << ' ';
            tt = 0;
        }
        ++tt;
    }
    cout << '\n';
    return 0;
}