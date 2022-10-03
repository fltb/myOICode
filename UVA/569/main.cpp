#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
using std::cin;
using std::cout;
const int MAXN = 10000 + 5;
int a[MAXN], n, m;
bool dfs(int x) {
    if (x == m + 1) {
        return a[x - 1] == n;
    }
    if (a[x - 1] * (1 << (m - x + 1)) < n || a[x - 1] > n || a[x - 1] <= a[x - 2]) {
        return false;
    }
    for (int i = x - 1; i >= 1; i--) {
        for (int j = x - 1; j >= 1; j--) {
            a[x] = a[i] + a[j];
            if (dfs(x + 1)) {
                return true;
            }
        }
    }
    return 0;
}
int main() {
    std::ios::sync_with_stdio(false);
    while (cin >> n && n != 0) {
        for (m = 1; m < MAXN; m++) {
            a[1] = 1;
            for (int i = 2; i <= m; i++) {
                a[i] = 0;
            }
            if (dfs(2)) {
                for (int i = 1; i <= m; i++) {
                    cout << a[i] << (i == m ? '\n' : ' ');
                }
                break;
            }
        }
    }
    return 0;
}