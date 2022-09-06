#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <iterator>
#include <set>
#define cosnt const;
using std::cin;
using std::cout;
using std::set;
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
const int MAXN = 4 + 2;
struct Point {
    int x, y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};
int n;
int gp[MAXN][MAXN], a[MAXN * MAXN];
bool vis[MAXN * MAXN];
Point curToP(int cur) {
    return Point(cur % n, cur / n);
}
int pToCur(Point x) {
    return x.x + x.y * n;
}
int& getGp(int cur) {
    auto p = curToP(cur);
    return gp[p.x][p.y];
}
int checkAll() {
    long long sumLinePre = -1, sumRowPre = -1;
    long long sumLine = 0, sumRow = 0;
    for (int i = 0; i < n; i++) {
        sumLine = 0;
        sumRow = 0;
        for (int j = 0; j < n; j++) {
            sumLine += gp[j][i];
            sumRow += gp[i][j];
        }
        if (sumLine != sumRow || (sumLinePre != -1 && sumLine != sumLinePre) || (sumRowPre != -1 && sumRowPre != sumRow)) {
            return -1;
        }
        sumLinePre = sumLine, sumRowPre = sumRow;
    }
    // 对角线
    long long lline = 0, rline = 0;
    for (int i = 0; i < n; i++) {
        lline += gp[i][i];
        rline += gp[n - 1 - i][i];
    }
    if (lline != rline || lline != sumLine) {
        return -1;
    }
    return sumLine;
}
bool suc = false;
void dfs(int cur) {
    if (cur == n * n) {
        // 边界了
        auto val = checkAll();
        if (val != -1) {
            cout << val << '\n';
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << gp[j][i] << (j == n - 1 ? '\n' : ' ');
                }
            }
            exit(0);
        }
        return;
    }
    for (int i = 0; i < n * n; i++) {
        auto now = a[i];
        if (!vis[i]) {
            vis[i] = 1;
            getGp(cur) = now;

            dfs(cur + 1);

            getGp(cur) = 0;
            vis[i] = 0;
        }
    }
}

long long recFirstLine;
void dfsCut(int cur) {
    if (cur == n * n) {
        // 边界了
        auto val = checkAll();
        if (val != -1) {
            cout << val << '\n';
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << gp[j][i] << (j == n - 1 ? '\n' : ' ');
                }
            }
            exit(0);
        }
        return;
    }

    const auto p = curToP(cur);
    // 假如是上一个是行的末尾
    if (p.y > 0 && p.x == 0) {
        long long line = 0ll;
        for (int j = 0; j < n; j++) {
            line += gp[j][p.y - 1];
        }

        if (p.y == 1) {  // 第一行
            recFirstLine = line;
        } else {
            if (line != recFirstLine) {  // 剪枝！
                return;
            }
        }
    }
    // 假如是上一个是列的末尾, 行肯定遍历完了
    if (p.y == n - 1 && p.x == 1) {
        long long row = 0ll;
        for (int j = 0; j < n; j++) {
            row += gp[p.x - 1][j];
        }
        if (recFirstLine != row) {  // 剪枝！
            return;
        }
    }
    for (int i = 0; i < n * n; i++) {
        auto now = a[i];
        if (!vis[i]) {
            vis[i] = 1;
            getGp(cur) = now;

            dfsCut(cur + 1);

            getGp(cur) = 0;
            vis[i] = 0;
        }
    }

    // 行末回退
    if (p.x == 0 && p.y == 1) {  // 第一行完（第二行开始）
        recFirstLine = 0;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n * n; i++) {
        cin >> a[i];
    }
    std::sort(&a[0], &a[n * n - 1]);
    if (n <= 2) {
        dfs(0);
    } else {
        dfsCut(0);
    }
    return 0;
}