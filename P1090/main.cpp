#include <iostream>
#include <vector>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
int main() {
    std::ios::sync_with_stdio (false);
    int n = 0, ans = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int tmp;
        cin >> tmp;
        q.push(tmp);
    }
    for (int i = 1; i < n; ++i) {
        int a = q.top();
        q.pop();
        int b = q.top();
        q.pop();

        ans += a + b;
        q.push(a + b);
    }
    cout << ans << endl;
    return 0;
}