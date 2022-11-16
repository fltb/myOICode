#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>
#define cosnt const
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
const int MAXN = 50000 + 3, MAXC = 26;
struct Node {
    int l, r;
    int ls, rs;
    int chs[MAXC];
    int lazy;
    Node(int ll = 0, int rr = 0) : l(ll), r(rr), lazy(-1) {}
};
Node nds[MAXN << 1];
std::string st;
int cnt = 1;
void genCHS(Node& me, Node& son) {
    for (int i = 0; i < MAXC; i++) {
        me.chs[i] += son.chs[i];
    }
}
void buildTree(int l, int r) {
    if (l == r) {
        nds[cnt].chs[st[l] - 'a']++;
        nds[cnt].l = l;
        nds[cnt].r = r;
        return;
    }
    auto me = cnt;
    auto m = (l + r) / 2;
    if (l <= m) {
        auto son = ++cnt;
        buildTree(l, m);
        genCHS(nds[me], nds[son]);
    }
    if (r >= m + 1) {
        auto son = ++cnt;
        buildTree(m + 1, r);
        genCHS(nds[me], nds[son]);
    }
}
void pushDown(int ndi){
    auto& nd = nds[ndi];
    if (nd.lazy!=-1) {
        if (nd.ls) {
            auto& lnd = nds[nd.ls];
            for (auto c = 0; c < MAXC; c++) {
                lnd.chs[c] = 0;
            }
            lnd.chs[nd.lazy] = lnd.r - lnd.l + 1;
        }
        if (nd.rs) {
            auto& rnd = nds[nd.rs];
            for (auto c = 0; c < MAXC; c++) {
                rnd.chs[c] = 0;
            }
            rnd.chs[nd.lazy] = rnd.r - rnd.l + 1;
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);

    return 0;
}