#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ios>
#include <iostream>
#include <unordered_set>
#define cosnt const
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
/*
预处理出来所有的完全平方数
可以在 O(1) 时间判断是不是完全平方数

一个性质：只有 316 个完全平方数
一个性质：最多达到 2*n-1 的大小
一个性质: n<10000

int sq[i];
一个可能的思路：从大到小枚举填入的数字，用一个 set 维护？
肯定超时，先写出来，没用也可以当对拍

剪过去了！！！
不可思议

题目里面有个隐含的单调性，就是映射出来的完全平方数单调递增，刚好对上了我的枚举顺序
所以 O(n**(n**0.5)) -> O(n)
难以置信的运气
*/
const int MAXN = 100000 + 3;
int sq[600];  // 也许快点吧，我想
bool isSq[2 * MAXN];
int n;
std::unordered_set<int> ust;
int arr[MAXN];
void init() {
    for (int i = 0; i < n; i++) {
        arr[i] = -1;
        ust.insert(i);
    }
}
bool dfs(int cur) {
    if (cur == 0) {
        if (isSq[*ust.begin()]) {
            arr[cur] = *ust.begin();
            return true;
        } else {
            return false;
        }
    }
    for (int i = sqrt(n + cur); sq[i] >= cur; i--) {
        if (ust.count(sq[i] - cur)) {
            ust.erase(sq[i] - cur);
            arr[cur] = sq[i] - cur;
#ifdef FLOATINGBLOCKS
            //cout << "At cur: " << cur << " try: " << sq[i] - cur << std::endl;
#endif
            if (dfs(cur - 1)) {
                return true;
            }
            arr[cur] = -1;
            ust.insert(sq[i] - cur);
        }
    }
    return false;
}
int main() {
    std::ios::sync_with_stdio(false);
    for (int i = 0; i * i < 2 * MAXN; i++) {
        sq[i] = i * i;
        isSq[i * i] = true;
    }
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        init();
        if (dfs(n - 1)) {
            for (int i = 0; i < n; i++) {
                cout << arr[i] << (i == n - 1 ? '\n' : ' ');
                #ifdef FLOATINGBLOCKS
                if (!isSq[arr[i]+i]) {
                    throw "ERR";
                }
                #endif
            }
        } else {
            cout << -1 << '\n';
        }
    }
    return 0;
}