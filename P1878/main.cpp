#include <iostream>
#include <queue>
using std::cout;
using std::cin;
using std::endl;
using std::priority_queue;
using std::abs;
const int MAXN = 2 * 100000 + 2;

struct Node {
    int a, b, val;
    Node() {}
    Node(int aa, int bb, int vv) : a(aa), b(bb), val(vv) {}
    bool operator<(const Node & x) const {
        bool flag;
        if (val > x.val) {
            flag = false;
        } else if (val < x.val) {
            flag = true;
        } else {
            if (a < x.a) {
                flag = true;
            } else {
                flag = false;
            }
        }
        flag = !flag;
        return flag;
    }
};

int gender[MAXN], val[MAXN], vis[MAXN], ans[MAXN][2], ans_cur, n;

int main() {
    std::ios::sync_with_stdio(false);
    priority_queue<Node> q;
    cin >> n;
    cin.get();
    for (int i = 1; i <= n; ++i) {
        char ch;
        cin >> ch;
        gender[i] = ch == 'B' ? 1 : 0;
    }
    cin.get();
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
    }
    for (int i = 1; i <= n-1; ++i) {
        if (gender[i] != gender[i+1]) {
            q.push(Node(i, i+1, abs(val[i] - val[i+1])));
        }
    }

    while (!q.empty()) {
        int cura = q.top().a;
        int curb = q.top().b;
        q.pop();
        if (vis[cura] || vis[curb]) {
            continue;
        }
        vis[cura] = 1;
        vis[curb] = 1;
        ++ans_cur;
        ans[ans_cur][0] = cura;
        ans[ans_cur][1] = curb;

        while (cura > 0 && vis[cura]) {
            --cura;
        }

        while (curb <= n && vis[curb]) {
            ++curb;
        }

        if (cura > 0 && curb <= n && gender[cura] != gender[curb]) {
            q.push(Node(cura, curb, abs(val[cura] - val[curb])));
        }

    }
    cout << ans_cur << endl;
    for (int i = 1; i <= ans_cur; ++i) {
    cout << ans[i][0] << " " << ans[i][1] << endl;
    }
}