#include <iostream>
#include <queue>
using std::cout;
using std::cin;
using std::endl;
using std::deque;

int m, n;

int main() {
    std::ios::sync_with_stdio (false);
    cin >> n >> m;
    deque<std::pair<int, int> > q;
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;

        while (!q.empty() && a < q.back().first) {
            q.pop_back();
        }
        while (!q.empty() && i - q.front().second >= m) {
            q.pop_front();
        }

        q.push_back(std::make_pair(a, i));

        if (i >= m) {
            cout << q.front().first << endl;
        }
    }

    return 0;
}