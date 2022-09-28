#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <functional>
#include <ios>
#include <iostream>
#include <set>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
/*/
先说下主框架。
是一个迭代加深搜索。

每一层跑函数的数组，拿出对应的可能状态数量，进行判断之后将该状态进入下一次层进行搜索。

状态：一个 long long，拿偏移量存状态
跑状态：跑一堆规则，一个一个加进去
拿状态：一个 vector 包含下一步可以到达的状态。
判断：快速判断有没有最小步数的方式还是超过了最大的深度限制

那么，开始吧！~
*/
const int MAXD = 23;

inline int idx(int x) {
    if (x >= 3 && x <= 13) {
        return x - 2;
    } else {
        return x ? x + 11 : 14;
    }
}
inline int getNum(long long s, int d) {
    return (s >> ((d - 1)) * 3) & 7ll;
}
inline long long changeNum(long long s, int d, int dc) {
    d = (d - 1) * 3;
    int dd = ((s >> d) & 7) + dc;
    return (s & (~((7ll << d)))) | ((long long)dd << d);
}
enum METHOD_ENUM {
    LINERS,         // 一，二，三顺子
    THREE_ONE_TWO,  // 三（带一二或不带）
    BOOMB_TWO,      // 炸弹或四带二
    SINGLE_PAIR,    // 单双加火箭
};
int lins[4][15];
long long dp[15][15];
void dfs(long long st, int d, int restrict);
bool liners(long long from, int d) {
    for (int i = 0; i < 3 * 15; i++) {
        lins[i / 15 + 1][i % 15] = 0;
    }

    for (int i = 1; i <= 12; i++) {
        switch (getNum(from, i)) {
        case 4:
        case 3:
            lins[3][i] = lins[3][i - 1] + 1;
        case 2:
            lins[2][i] = lins[2][i - 1] + 1;
        case 1:
            lins[1][i] = lins[1][i - 1] + 1;
        }
    }
    int rt = false;
    for (int i = 12; i >= 2; i--) {
        for (int j = 1; j <= 3; j++) {
            int jump = (j > 1 ? 3 - (j - 2) : 5);
            if (lins[j][i] >= jump) {
                rt = true;
                for (int i = 0; i < 15; i++) {
                    for (int j = 0; j < 15; j++) {
                        dp[i][j] = 0;
                    }
                }
                for (int len = jump; len <= lins[j][i]; len++) {
                    for (int l = i - lins[j][i] + 1; l + len - 1 <= i; l++) {
                        int r = l + len - 1;
                        auto st = 0ll;
                        if (len == jump) {
                            st = from;
                            for (int k = l; k <= r; k++) {
                                st = changeNum(st, k, -j);
                            }
                        } else {
                            st = dp[l][r - 1];
                            st = changeNum(st, r, -j);
                        }
                        dp[l][r] = st;
                        dfs(st, d + 1, LINERS);
                    }
                }
                for (int k = i - lins[j][i] + 1; k <= i; k++) {
                    lins[j][k] = 0;
                }
                /* 这里贪心一下
                auto st = from;
                for (int m = i - lins[j][i] + 1; m <= i; m++) {
                    st = changeNum(st, m, -j);
                    lins[j][m] = 0;  // 为了伟大的贪心！
                }*/
            }
        }
    }
    return rt;
}
bool threeOneTwo(long long from, int d) {
    bool rt = false;
    for (int i = 1; i <= 13; i++) {
        if (getNum(from, i) >= 3) {
            rt = true;
            auto st = changeNum(from, i, -3);
            dfs(st, d + 1, THREE_ONE_TWO);
            for (int j = 1; j <= 14; j++) {
                if (j == i) {
                    continue;
                }
                auto d = getNum(st, j);
                if (j != i) {
                    if (d >= 2 && j != 14) {
                        dfs(changeNum(st, j, -2), d + 1, THREE_ONE_TWO);
                    }
                    if (d >= 1) {
                        dfs(changeNum(st, j, -1), d + 1, THREE_ONE_TWO);
                    }
                }
            }
        }
    }
    return rt;
}
bool boombTwo(long long from, int d) {
    bool rt = false;
    for (int i = 1; i <= 13; i++) {
        if (getNum(from, i) == 4) {
            rt = true;
            auto st = changeNum(from, i, -4);
            // 四带几
            dfs(st, d + 1, BOOMB_TWO);
            /*for (int j = 1; j <= 14; j++) {
                if (j == i) {
                    continue;
                }
                auto tmp = getNum(st, j);
                if (tmp >= 2) {
                    auto stt = changeNum(st, j, -2);
                    dfs(stt, d + 1, BOOMB_TWO);
                    if (j == 14) {
                        break;  // 防止把大小王算进对子
                    }
                    for (int k = j + 1; k <= 13; k++) {
                        if (getNum(stt, k) >= 2) {
                            dfs(changeNum(stt, k, -2), d + 1, BOOMB_TWO);
                        }
                    }
                }
                if (tmp >= 1) {
                    auto stt = changeNum(st, j, -1);
                    for (int k = j + 1; k <= 14; k++) {
                        if (getNum(stt, k) >= 1) {
                            dfs(changeNum(stt, k, -1), d + 1, BOOMB_TWO);
                        }
                    }
                }
            }*/
            // 四带一对 或者 两对
            for (int j = 1; j <= 14; j++) {
                if (i != j && getNum(st, j) >= 2) {
                    auto aPair = changeNum(st, j, -2);
                    dfs(aPair, d + 1, BOOMB_TWO);
                    for (int k = j + 1; k <= 13; k++) {
                        if (getNum(aPair, k) >= 2) {
                            dfs(changeNum(aPair, k, -2), d + 1, BOOMB_TWO);
                        }
                    }
                }
            }

            for (int j = 1; j <= 14; j++) {
                if (i != j && getNum(st, j) >= 1) {
                    auto aSigle = changeNum(st, j, -1);
                    for (int k = j + 1; k <= 14; k++) {
                        if (getNum(aSigle, k) >= 1) {
                            dfs(changeNum(aSigle, k, -1), d + 1, BOOMB_TWO);
                        }
                    }
                }
            }
        }
    }
    return rt;
}
// 改写一下，直接迭代
bool singlePair(long long from, int d) {
    bool rt = false;
    int steps = 0;
    for (int i = 1; i <= 14; i++) {
        auto d = getNum(from, i);
        while (d >= 2) {
            rt = true;
            d -= 2;
            steps++;
        }
        while (d >= 1) {
            rt = true;
            d -= 1;
            steps++;
        }
    }
    dfs(0, d + steps, SINGLE_PAIR);
    return rt;
}
bool (*methods[])(long long, int) = {
    liners,
    threeOneTwo,
    boombTwo,
    singlePair};
long long arr2st(int arr[]) {
    long long st = 0ll;
    for (int i = 0; i < 14; i++) {
        st = changeNum(st, i + 1, arr[i]);
    }
    return st;
}

void ptSt(long long st) {
    for (int i = 1; i <= 14; i++) {
        cout << getNum(st, i) << ' ';
    }
    cout << std::endl;
}

int cnt = 0;
std::set<long long> sts;
void dfs(long long st, int d, int restrict) {
    cnt = (restrict == SINGLE_PAIR) ? d : cnt + 1;
    if (sts.count(st)) {
        cout << "At " << restrict << " found!\n";
    }
    ptSt(st);
    sts.insert(st);
}

int as[4][3][14] = {
    // LINER
    {{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 2, 0, 0 },
     {0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 1, 1, 1, 1, 1, 0, 2, 0, 0, 0, 0}},
    // THREE
    {{0, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 3, 1, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2},
     {4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    // BOOM
    {{4, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
     {4, 1, 4, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {4, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    // SIGNLE PAIR
    {{1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
     {2, 2, 3, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
     {1, 4, 3, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2}}};

int main() {
    for (int i = LINERS; i <= SINGLE_PAIR; i++) {
        for (int j = 0; j < 3; j++) {
            cnt = 0;
            sts.clear();
            auto st = arr2st(as[i][j]);
            methods[i](st, 0);
            cout << "CASE " << i << " :\n";
            cout << cnt << std::endl;
        }
    }
    return 0;
}
