#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>
#define cosnt const
using std::cin;
using std::cout;
using std::vector;
template <typename T>
inline void read(T& t) {
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
// 保证单调性就行了吧应该是吧
// 确保先递增后递减
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (auto& a : arr) {
            cin >> a;
        }
        // i 是当前递增到的长度， j 是从尾到头的长度
        int i = 1, j = 1;
        while (i < n && arr[i - 1] <= arr[i]) {
            i++;
        }
        while (j < n && arr[n - j] <= arr[n - j - 1]) {
            j++;
        }
        cout << (i + j >= n ? "YES" : "NO") << '\n';
    }
    return 0;
}
