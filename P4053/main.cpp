#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
const int MAXN = 150000 + 2;

struct Building {
    int cost;
    int total;
    Building() {}
    Building(int c, int t) : cost(c), total(t) {}
    bool operator<(const Building & x) const {
        return total < x.total;
    }
};
struct MyLess {
    bool operator()( const Building & a, const Building & b ) const {
        return a.cost < b.cost;
    }
};
Building b[MAXN];
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int c, t;
        cin >> c >> t;
        b[i] = Building(c, t);
    }
    std::sort(b + 1, b + 1 + n);
    std::priority_queue<Building,
                        std::vector<Building>,
                        MyLess> q;
    int time_now = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        Building & now = b[i];
        if (time_now + now.cost > now.total) {
            Building bb = q.top();
            if (now.cost < bb.cost) {
                q.pop();
                q.push(now);
                time_now -= bb.cost;
                time_now += now.cost;
            }
        } else {
            ++ans;
            time_now += now.cost;
            q.push(now);
        }
    }
    cout << ans << endl;
    return 0;
}