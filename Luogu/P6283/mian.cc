#include <algorithm>
#include <iostream>
#include <stack>
using std::cin;
using std::cout;
using std::stack;
struct P {
    int x, y;
    P(int xx = 0, int yy = 0) {
        x = xx, y = yy;
    }
    bool operator<(const P& b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
};
P a[100000 + 2];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = P(x, y);
    }
    std::sort(a, a + n);
    stack<P> st;
    st.push(a[0]);
    for (int i = 1; i < n; i++) {
        P t = a[i];
        if (t.y < st.top().y) {
            st.push(t);
        } else {
            P t1 = st.top();
            st.pop();
            while (!st.empty() && st.top().y <= t.y) {
                st.pop();
            }
            st.push(t1);
        }
    }
    cout << st.size();
}