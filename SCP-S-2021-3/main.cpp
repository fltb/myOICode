/*
这个先写个 dfs 骗分算了
*/
#include <iostream>
#include <queue>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
const int MAXN = 2000 + 2; // 那几个大的不管了
enum {
    L = 2,
    R = 3
};

int a[MAXN], n, T,
    b[MAXN], curb = 1, fnd = false;
int c[MAXN], cur_start = 1, cur_end = 2 * n;

void init() {
    for (int i = 0; i < MAXN; ++i) {
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }
    curb = 1;
    fnd = false;
    cur_start = 1;
    cur_end = 2 * n;
}

bool get_ans(int i) {
    if (i >= curb) {
        int flag = true;
        for (int i = 1; i <= n; ++i) {
            if (c[i] != c[2 * n - i + 1]) {
                flag = false;
            }
            return flag;
        }
    }
    if (b[i] == L) {
        c[i] = a[cur_start++];
    } else {
        c[i] = a[cur_end--];
    }
    return get_ans(i + 1);
}

void dfs(int first, int last) {
    int deep = 2 * n - (last - first + 1);
    if (fnd) {
        return;
    }
    if (first >= last) { // end
        get_ans(1);
    }
    b[deep] = L;
    dfs(first + 1, last);
    b[deep] = 0;

    b[deep] = R;
    dfs(first, last - 1);
    b[deep] = 0;
}

int main() {
    cin >> T;
    while (T > 0) {
        cin >> n;
        init();
        if (n > MAXN) {
            cout << -1 << endl;
            continue;
        }
        for (int i = 1; i <= n*2; ++i) {
            cin >> a[i];
        }
        dfs(1, 2 * n);
        if (fnd) {
            for (int i = 1; i < curb; ++i) {
                cout << b[i];
            }
            cout << endl;
        } else {
            cout << -1 << endl;
        }
    }
    
}
