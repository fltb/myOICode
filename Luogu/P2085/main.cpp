#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl; 
using std::stack;
using std::priority_queue;

struct Function {
    int a, b, c;
    Function() {}
    Function(int aa, int bb, int cc) : a(aa), b(bb), c(cc) {}
    int get(int x) const {
        return a*(x*x) + b*x + c;
    }
};

int main () {
    int n, m;
    cin >> n >> m;
    priority_queue<int> que;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        Function fun = Function(a, b, c);
        int cur = 1;
        while (que.size() < m) {
            que.push(fun.get(cur++));
        }
        while (que.top() > fun.get(cur)){
            que.pop();
            que.push(fun.get(cur++));
        }
    }
    stack<int> stck;
    while(!que.empty()) {
        stck.push(que.top());
        que.pop();
    }
    while(!stck.empty()) {
        cout << stck.top() << " ";
        stck.pop();
    }
    cout << endl;
    return 0;
}