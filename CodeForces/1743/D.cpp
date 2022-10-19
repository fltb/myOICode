#include <algorithm>
#include <bitset>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const
using std::bitset;
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
const int MAXN = 2e6 + 2;
int n;
bool operator<(const bitset<MAXN>& a, const bitset<MAXN>& b) {
    for (int i = 0; i < n; i++) {
        if (a.test(i) != b.test(i)) {
            return a.test(i) < b.test(i);
        }
    }
    return false;
}
int findIdx(const bitset<MAXN>& a, int start, int val) {
    for (int i = start; i < n; i++) {
        if (val == a.test(i)) {
            return i;
        }
    }
    return -1;
}
#ifdef FLOATINGBLOCKS
void ptSt(const bitset<MAXN>& mxB) {
    int start = 0;
    while (start < n && !mxB.test(start)) {
        start++;
    }
    for (int i = start; i < n; i++) {
        cout << (mxB.test(i) ? '1' : '0');
    }
    cout << std::endl;
}
#endif
int main() {
    std::ios::sync_with_stdio(false);
    cin >> n;
    cin.get();
    bitset<MAXN> bt;
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        bt.set(i, ch == '1');
    }
    int mxl = n;
    while (mxl > 0 && !bt.test(n - mxl)) {
        mxl--;
    }
    if (!mxl) {
        cout << 0 << '\n';
        return 0;
    }
    auto mxB = bt;
    // 先打个暴力再思考一下
    /*for (int len = 1; len <= mxl; len++) {
        for (int idx = n - mxl; idx + len <= n; idx++) {
            if (!bt.test(idx)) {
                continue;
            }
            auto now = bt;
            for (int i = 0; i < len; i++) {
                auto cur = n - len + i;
                now.set(cur, bt.test(cur) | bt.test(i));
            }
            if (mxB < now) {
                mxB = now;
            }
        }
    }*/
    // 对于原串右移几位
    // 就差一步就到正解了
    /*
    for (int mv = 1; mv < n; mv++) {
        auto mved = bt << mv;
        auto now = bt | mved;
        if (mxB < now) {
            mxB = now;
        }
    }*/

    int start = findIdx(bt, 0, 1), first0 = findIdx(bt, start, 0);
    for (int mv = 1; mv <= first0 - start; mv++) {  // 尝试将前面的不断进行右移，长度从 1 到 first0 - start
        auto mved = bt << mv;
        auto now = bt | mved;
        if (mxB < now) {
            mxB = now;
        }
    }
    while (start < n && !mxB.test(start)) {
        start++;
    }
    for (int i = start; i < n; i++) {
        cout << (mxB.test(i) ? '1' : '0');
    }
    cout << '\n';
    return 0;
}