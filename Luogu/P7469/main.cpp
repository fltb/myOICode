#include <algorithm>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <unordered_set>
#define cosnt const
using std::cin;
using std::cout;
using std::string;
using std::unordered_set;
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
现在进行下面的思考
    从 b 中截取连续的一段，如果是 a 串的子序列，说明是个可行的方案
    把 a 串映射掉？好像没啥用……
    反过来想想看？
    遍历 a， 构造子序列 选 or 不选 -> a 下标 b 下标 长度 = 数量 ？
    dp[现在在哪里][b 的第几位][序列长度] = 方案数
    60 分做法，先看看吧

题目读错了，结束（

    重来啦
*/
const int MAXN = 3000 + 3;
char a[MAXN], b[MAXN];
unsigned long hs[MAXN * MAXN], cnt;
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    cin.get();
    cin >> (a + 1);
    cin.get();
    cin >> (b + 1);
    auto hasher = std::hash<string>();
    for (int i = 1; i <= n; i++) {
        string bs = "";
        int ac = 1;
        for (int j = i; j <= n; j++) {
            auto c = b[j];
            bs += c;
            while (ac <= n && a[ac] != b[j]) {
                ac++;
            }
            if (ac > n) {
                break;
            }
            ac++;
            hs[cnt++] = hasher(bs);
        }
    }
    std::sort(hs, hs+cnt);
    cout << (std::unique(hs, hs + cnt) - hs) << '\n';
    return 0;
}