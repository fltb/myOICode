#include <algorithm>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <queue>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::get;
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
const int MAXN = 2e5 + 2;

/*
dp[当前列][当前行][上次在哪行] = 到达当前格子的时候最大的值
dp[MAXN][2][2]
*/
int main() {
// 哪天接着写好了

}

/**
 * 嘿嘿嘿全错嘿嘿嘿
 * 

    int line;
    int row;
    Pointer(int l = 0, int r = 0) : line(l), row(r) {}
};
class Linker {
    std::vector<Pointer> l[2][MAXN];

   public:
    std::vector<Pointer>& operator[](const Pointer& cur) {
        return l[cur.line][cur.row];
    }
} links;
bool graph[2][MAXN], hason[2][MAXN], inq[2][MAXN];
int deep[2][MAXN];
int recD[2][MAXN]{{-1}, {-1}};
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int j = 0; j < 2; j++) {
        cin.get();
        for (int i = 1; i <= n; i++) {
            char ch;
            cin >> ch;
            if (ch == '1') {
                graph[j][i] = true;
            } else {
                graph[j][i] = false;
            }
            recD[j][i] = -1;
        }
    }

    queue<Pointer> q;
    q.push(Pointer(0, 1));
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        for (int i = now.row + 1; i <= n + 1; i++) {
            bool bk = false;
            auto tmp = [&bk, &q, &now](int x, int y) {
                if (graph[x][y]) {
                    if (!inq[x][y]) {
                        q.push(Pointer(x, y));
                        deep[x][y] = deep[now.line][now.row] + 1;
                        inq[x][y] = 1;
                    }
                    if (deep[x][y] >= deep[now.line][now.row]) {
                        hason[now.line][now.row] = 1;
                        links[Pointer(x, y)].push_back(now);
                    }
                    bk = true;
                }
            };
            tmp(now.line, i);
            tmp(now.line ^ 1, i - 1);
            if (bk) {
                break;
            }
        }
    }
    queue<Pointer> qA;
    for (int i = 1; i <= n; i++) {
        if (graph[1][i] && !hason[1][i]) {
            qA.push(Pointer(1, i));
        }
        if (graph[0][i] && !hason[0][i]) {
            qA.push(Pointer(0, i));
        }
    }

    std::function<int(Pointer)> dfs = [&dfs](Pointer x) {
        int& rec = recD[x.line][x.row];
        if (rec != -1) {
            return rec;
        }
        if (x.line == 0 && x.row == 1) {
            return rec = 0;
        }
        for (auto to : links[x]) {
            rec = max(rec, dfs(to) + 1);
        }
        return rec;
    };

    int cnt = 0;
    while (!qA.empty()) {
        auto now = qA.front();
        qA.pop();
        cnt = max(cnt, dfs(now));
    }
    cout << cnt << '\n';
    return 0;
}*/