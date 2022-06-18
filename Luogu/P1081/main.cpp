/*
# 思路

## 数据表示

采用一个 City 结构来存储 height number，同时可以比较大小

## 建图

可以给所有的 City 排序(nlogn)，然后给每个 City 都算出来 next_a next_b

## 过程

### 通法

原来的：跑普通的 DP，先从 A 开始，再从 B 开始，状态有 now， x_left，存的是 anow, bnow，也许可以套记忆化。
优化之后：从终点开始向出发点走 DP，然后记下从出发点走到这个点所需的 a 和 b
最终：换成步数了

### 问 1

遍历每个城市区间

### 问 2

不断计算到最后

### 优化

我们可以发现大部分都是重复计算，前一个需要走的都是从最后一个不能走到的点转化来的，
可以用类似区间的思想，枚举从每个顶点走到每个终点的 x ，然后就完成了。

*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::string;
const int MAXN = 1000+2,
          INF  = 2147483647;
const double EQUAL = 1e-6;

bool judge_equal(int a1, int b1, int a2, int b2) {
    if ( (b1 == 0 && b2 != 0) || (b1 != 0 && b2 == 0)) {
        return false;
    }
    if (b1 == 0) {
        return true;
    }
    if ((double)a1 / (double)b1 - EQUAL < (double)a2 / (double)b2 
        && (double)a1 / (double)b1 + EQUAL > (double)a2 / (double)b2) {
        return true;
    } else {
        return false;
    }
}

// if a1/b1 < a2/b2
bool judge(int a1, int b1, int a2, int b2) {
    if ((b1 == 0 && b2 != 0) || (b1 != 0 && b2 == 0)) {
        if (b1 == 0) {
            return false;
        } else {
            return true;
        }
    }
    if (judge_equal(a1, b1, a2, b2)) {
        return false;
    }
    
    return (double)a1 / (double)b1 < (double)a2 / (double)b2;
}

struct City {
    int h, x, a_to, b_to;
    City(){}
    City(int height, int number) : h(height), x(number) {}
    bool operator<(const City & x) const {
        return h < x.h;
    }
    int get_dis(const City & x) const {
        return std::abs(h - x.h);
    }
};

City citys[MAXN];
int n, dp[MAXN][MAXN][3]; // begin, step, a's wtaval(0), b's val(1), city(2)

int main() {
    std::ios::sync_with_stdio(false);
    std::freopen("out.txt", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> citys[i].h;
        citys[i].x = i;
    }
    // 这里是 n^2 的建图
    for (int i = 1; i <= n; ++i) {
        int min_val = INF,
            min_cur = 0,
            second_min_val = INF,
            second_min_cur = 0;
        for (int j = i + 1; j <= n; ++j) {
            int dis = citys[i].get_dis(citys[j]);
            if (dis < min_val || (dis == min_val && citys[j] < citys[min_cur])) {
                second_min_cur = min_cur;
                second_min_val = min_val;
                min_val = dis;
                min_cur = j;
            } else if (dis < second_min_val || (dis == second_min_val && citys[j] < citys[min_cur])){
                second_min_cur = j;
                second_min_val = dis;
            }
        }
        citys[i].a_to = min_cur;
        citys[i].b_to = second_min_cur;
        //citys[min_cur].a_from = i;
        //citys[second_min_cur].b_from = i;
    }
    // dp init
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j][0] = INF;
            dp[i][j][1] = INF;
        }
    }
    // dp
    for (int i = 1; i <= n; ++i) {
        int cur = i,
            step = 0,
            s = 1; // 这次往 a 还是 b
        dp[i][0][0] = 0;
        dp[i][0][1] = 0;
        dp[i][0][2] = i;

        do {
            int pre_cur = cur;
            if (s) { 
                cur = citys[cur].b_to;
                dp[i][step+1][1] = dp[i][step][1]; // b haven't changed
                dp[i][step+1][0] = dp[i][step][0] + citys[cur].get_dis(citys[pre_cur]); // added b
                dp[i][step+1][2] = cur;
            } else { 
                cur = citys[cur].a_to;
                dp[i][step+1][1] = dp[i][step][1] + citys[cur].get_dis(citys[pre_cur]); // added a
                dp[i][step+1][0] = dp[i][step][0]; // a haven't changed  
                dp[i][step+1][2] = cur;              
            }
            s = 1 - s;
            ++step;
        } while (s ? citys[cur].b_to: citys[cur].a_to);
    }

    // problem 1
    int x0, start = 0, aaa = 0, bbb = 0;
    cin >> x0;
    for (int i = 1; i <= n; ++i) {
        for (int j = n; j >= 0; --j) {
            int (&now)[3] = dp[i][j];
            if (0 == now[2]) {
                continue;
            }
            if (now[0] + now[1] > x0) {
                continue;
            }
            if (judge(now[0], now[1], aaa, bbb) || (judge_equal(now[0], now[1], aaa, bbb) 
                && citys[start].h < citys[i].h)) {
                aaa = now[0];
                bbb = now[1];
                start = i;
            }
            break;
        }
    }
    cout << start << "\n";

    // problem 2
    int m;
    cin >> m;
    while (m > 0) {
        --m;
        int s, x;
        bool vis = false;
        cin >> s >> x;
        for (int i = n; i >= 0; --i) {
            int (&now)[3] = dp[s][i];
            if (!now[2]) {
                continue;
            }
            if (now[0] + now[1] > x) {
                continue;
            }
            vis = true;
            cout << now[0] << " " << now[1] << "\n";
            break;
        }
        if (!vis) {
            cout << 0 << " " << 0 << "\n";
        }
    }

    return 0;
}
