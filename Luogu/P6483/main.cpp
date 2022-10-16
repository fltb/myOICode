#include <iostream>
using std::cin;
using std::cout;
const int MAXN = 2e6 + 5;
int max(int a, int b) {
    return a < b ? b : a;
}
int min(int a, int b) {
    return a < b ? a : b;
}
int main() {
    int s, c;
    cin >> c >> s;
    for (int m = 2; m < MAXN; m++) {
        auto n = c / 2 - m + 2;
        if (max(0, (n - 2) * (m - 2)) == s) {
            cout << max(n, m) << ' ' << min(n, m) << '\n';
            return 0;
        }
    }
    return 0;
}