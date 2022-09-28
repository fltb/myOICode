#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::string;
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
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        vector<string> ss;
        cin.get();
        for (int i = 0; i < n; i++) {
            string tmp;
            std::getline(cin, tmp);
            ss.push_back(tmp);
        }
        std::nth_element(ss.begin(), ss.begin() + (n / 2 - 1), ss.end());
        std::nth_element(ss.begin(), ss.begin() + (n / 2), ss.end());
        auto &s1 = ss[n / 2 - 1], s2 = ss[n / 2];
#ifdef FLOATINGBLOCKS
        cout << s1 << ' ' << s2 << '\n';
#endif
        auto ans = "";
        int i = 0;
        int flag = 0;
        for (i = 0; i < min(s1.length(), s2.length()); i++) {
            if (s1[i] == s2[i]) {
                ans += (char)s1[i];
            } else {
                ans += char((char)s1[i] + 1);
                flag = 1;
                break;
            }
        }
        if (i < s1.length() && !flag) {
            ans += char((char)s1[i] + 1);
        }
        cout << ans << '\n';
    }
    return 0;
}