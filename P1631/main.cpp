#include <iostream>
#include <queue>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::sort;
using std::priority_queue;
const int MAXN = 100000 + 2;

struct Node {
    int val, cur_a, cur_b;
    Node(){}
    Node(int v, int ca, int cb) : val(v), cur_a(ca), cur_b(cb) {}
    bool operator<(const Node & x) const {
        return val > x.val;
    }
};

int a[MAXN], b[MAXN];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    sort(a+1, a+n+1);
    sort(b+1, b+n+1);

    priority_queue<Node> q;
    for (int i = 1; i <= n; ++i) {
        q.push(Node(a[i] + b[1], i, 1));
    }

    for (int cnt = 1; cnt <= n; ++cnt) {
        Node now = q.top();
        q.pop();

        cout << now.val << " ";
        if (now.cur_b + 1 <= n) {
            q.push(Node(a[now.cur_a] + b[now.cur_b+1], now.cur_a, now.cur_b+1));
        }
    }
    cout << endl;
    return 0;
}