#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <functional>
#include <ios>
#include <iostream>
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
/*
状态定义：
因为顺子的判断问题，我们把斗地主的牌重排一下，大王小王没用，直接压一块
                 1112 13 1  2  0
3 4 5 6 7 8 9 10 J Q  K  A  2  小王+大王
1 2 3 4 5 6 7 8  9 10 11 12 13 14
*/
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
void dfs(long long st, int d, int restrict);
bool liners(long long from, int d) {
    int lins[3][15];
    long long dp[15][15];
    for (int i = 0; i < 3 * 15; i++) {
        lins[i / 15][i % 15] = 0;
    }

    for (int i = 1; i <= 12; i++) {
        switch (getNum(from, i)) {
        case 4:
        case 3:
            lins[3-1][i] = lins[3-1][i - 1] + 1;
        case 2:
            lins[2-1][i] = lins[2-1][i - 1] + 1;
        case 1:
            lins[1-1][i] = lins[1-1][i - 1] + 1;
        }
    }
    int rt = false;
    for (int i = 12; i >= 2; i--) {
        for (int j = 1; j <= 3; j++) {
            int jump = (j > 1 ? 3 - (j - 2) : 5);
            if (lins[j-1][i] >= jump) {
                rt = true;
                for (int i = 0; i < 15; i++) {
                    for (int j = 0; j < 15; j++) {
                        dp[i][j] = 0;
                    }
                }
                for (int len = jump; len <= lins[j-1][i]; len++) {
                    for (int l = i - lins[j-1][i] + 1; l + len - 1 <= i; l++) {
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
                for (int k = i - lins[j-1][i] + 1; k <= i; k++) {
                    lins[j-1][k] = 0;
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
                auto dd = getNum(st, j);
                if (j != i) {
                    if (dd >= 2 && j != 14) {
                        dfs(changeNum(st, j, -2), d + 1, THREE_ONE_TWO);
                    }
                    if (dd >= 1) {
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
        auto dd = getNum(from, i);
        while (dd >= 2) {
            rt = true;
            dd -= 2;
            steps++;
        }
        while (dd >= 1) {
            rt = true;
            dd -= 1;
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
#ifdef FLOATINGBLOCKS
void ptSt(long long st) {
    for (int i = 1; i <= 14; i++) {
        cout << getNum(st, i) << ' ';
    }
    cout << std::endl;
};
long long ss[200];
#endif
int ans = MAXD;
void dfs(long long st, int d, int restrict) {
#ifdef FLOATINGBLOCKS
    ss[d] = st;
#endif
    if (d >= ans) {  // 你已经没有价值了~
        return;
    }
    if (!st) {  // 无了
        ans = min(ans, d);
#ifdef FLOATINGBLOCKS
        cout << ans << ":\n";
        for (int i = 0; i < ans; i++) {
            ptSt(ss[i]);
        }
#endif
    }
    for (int i = restrict; i < 4; i++) {
        methods[i](st, d);
    }
}

/*

bool testCases() {
    long long iniSt = 0;
    for (int i = 1; i <= 10; i++) {
        iniSt = changeNum(iniSt, i, 3);
    }
    vector<long long> store;
    auto ptSt = [](long long st) {
        for (int i = 1; i <= 10; i++) {
            cout << getNum(st, i) << ' ';
        }
        cout << std::endl;
    };
    auto ptS = [&ptSt](vector<long long>& store) {
        for (auto& st : store) {
            ptSt(st);
        }
    };
    ptSt(iniSt);
    if (methods[LINERS](iniSt, store)) {
        cout << "Pass Liners: ";
        ptS(store);
    } else {
        cout << "Liners Error";
        return false;
    }
    store.clear();
    iniSt = 0;
    iniSt = changeNum(0, 3, 4);
    iniSt = changeNum(iniSt, 1, 2);
    iniSt = changeNum(iniSt, 2, 1);
    iniSt = changeNum(iniSt, 5, 3);

    if (methods[THREE_ONE_TWO](iniSt, store)) {
        cout << "Pass three";
        ptS(store);
    } else {
        cout << "THREE TWO ONE Error";
        return false;
    }
    store.clear();
    if (methods[BOOMB_TWO](iniSt, store)) {
        cout << "Pass BOOM:\n";
        ptS(store);
    } else {
        cout << "BOOM Error\n";
        return false;
    }
    return true;
}*/

int main() {
#ifdef FLOATINGBLOCKS
    int testing[15];
    //freopen("landlords7.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    int T, n;
    cin >> T >> n;
    while (T--) {
        long long iniSt = 0;
#ifdef FLOATINGBLOCKS
        for (int i = 0; i <= 14; i++) {
            testing[i] = 0;
        }
#endif
        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            iniSt = changeNum(iniSt, idx(a), 1);
#ifdef FLOATINGBLOCKS
            testing[idx(a)]++;
#endif
        }
        ans = MAXD;
#ifdef FLOATINGBLOCKS
        if (T <= 100 - 20) {
            for (int i = 0; i <= 14; i++) {
                cout << testing[i] << " ";
            }
            cout << '\n';
            ptSt(iniSt);
            cout << std::endl;
        }
#endif
        dfs(iniSt, 0, LINERS);
        cout << ans << '\n';
    }
    return 0;
}
