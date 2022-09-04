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
int gcd(int a, int b) {
    return (b > 0) ? gcd(b, a % b) : a;
}
int main() {
#ifdef FLOATINGBLOCKS
    freopen("task5.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    int n, x, p, q;
    cin >> n >> x >> p >> q;
    int g = gcd(p, q);
    p /= g;
    q /= g;
    long long sleepQ = 0, rest = x, day = 1;
    while (n--) {
        int task;
        cin >> task;
        //一直到可以执行这个工作
        /*
        现在我们想象一种更快的方法，可以尝试让 day 不是一个一个加上去，而是一次多个加上去
        那么我们看下需要 多长的时间 的 完全的睡觉 可以让一天的工作时间 变大多少小时 。
        第 day 天需要 day * x * p / q 小时的总睡觉时间
        睡觉 d 天可以让时间增加 x*d 那么……
        找到一个 d， 使得 task + (day * x * p / q) >= (sleep + x * d)
                        task+q + (day+d) * x * p >= sleepQ + x * d*q

        边界好烦啊，不如枚举二进制吧，1<<i-1不满足， 1<<i 满足，这两个之间再二分，最后丢给那个while，Over！
        */
        /*int d = 0;
        for (int i = 0; i < 10; i++) {
            int dd = (1 << i);
            if (task * q + (day + dd) * x * p >= sleepQ + x * dd * q) {
                d = dd;
                break;
            }
        }
        int l = 0, r = d-1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (task * q + (day + mid) * x * p < sleepQ + x * mid * q) {
                l = mid + 1;
                d = mid;
            } else {
                r = mid - 1;
            }
        }
        // 一次性给加上 d
        if (d > 1) {
            sleepQ += (long long)x * (d-1) * q + rest * q;
            day += d;
            rest = x;
        }*/
        while (true) {
            if (rest > task && (long long)sleepQ + (long long)(rest - task) * q >= day * x * p) {
                rest -= task;
                break;
            }
            day += 1;
            sleepQ += (long long)rest * q;
            rest = x;
        }
    }
    cout << day - (x == rest ? 1 : 0) << '\n';
    return 0;
}