#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using std::cin;
using std::cout;
using std::endl;
using std::multiset;
const int MAXN = 2*100000 + 2;

struct MySet {
    multiset<int> st;
    multiset<int>::iterator it;
    bool inited;
    MySet(int first) {
        st.insert(first);
    }
    void add(int val) {
        st.insert(val);
        if (!inited) {
            return;
        }
        if (val < *it) {
            --it;
        }
    }
    int get() {
        if (!inited) {
            it = st.begin();
            inited = true;
            return *it;
        }
        ++it;
        return *it;
    }
};

int a[MAXN], u[MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> u[i];
    }
    MySet st1(a[1]);
    int cur = 1;
    while (u[cur] == 1) {
        cout << st1.get() << endl;
        ++cur;
    }
    for (int i = 2; i <= m; ++i) {
        st1.add(a[i]);
        while (u[cur] == i) {
            cout << st1.get() << endl;
            ++cur;
        }
    }
    return 0;
}