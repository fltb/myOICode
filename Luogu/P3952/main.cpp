#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>
#include <ios>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define cosnt const
using std::array;
using std::cin;
using std::cout;
using std::set;
using std::stack;
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
/*
一般流程讲一遍吧。
首先做语法检查？这样至少不至于全部写错
那么来吧
用一个 vector string 读入
接着判断是否 F 与 E 匹配
同时用 set<srting> 来记录当前用过的变量名字，如果重复出现就 ERR

然后就是计算环节了。
对于每层循环看复杂度。一个变量 n = 0 存 n 的几次，
如果 x y 都是常数
    x > y 后面都不会执行了，直接结束计算
    x <= y 那就贡献 O(1)，意思是不贡献
如果 x 是 n 而且 y 不是 n
    同样不会执行 结束
如果 y 是 n
    n++
如果两个都是 n
    执行一次，不贡献

最后判断是不是和读入的一样，Over
*/
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int l;
        cin >> l;
        string oo;
        cin >> oo;
        int ns = 0;
        if (oo[2] == 'n') {
            int i = 4;
            while (std::isdigit(oo[i])) {
                char cc = oo[i];
                ns = ns * 10 + int(cc - '0');
                i++;
            }
        }
        auto genOC = [](const array<string, 3>& a) {
            auto isDt = [](const string& st) {
                auto isdigi = true;
                for (auto c : st) {
                    isdigi = isdigi && std::isdigit(c);
                }
                return isdigi;
            };
            if (!isDt(a[1])) {
                if (isDt(a[2])) {
                    return -1;
                } else {
                    return 0;
                }
            } else if (!isDt(a[2])) {
                return 1;
            } else {
                auto x = std::stoi(a[1]), y = std::stoi(a[2]);
                if (x > y) {
                    return -1;
                }
            }
            return 0;
        };
        // syntax check
        stack<array<string, 3>> loops;
        vector<int> rec;  // 每个深度的最大贡献
        int cnt = 0, flag = 0;
        set<string> is;
        int oc = 0;
        while (l--) {
            char mode;
            cin >> mode;
            cin.get();
            if (mode == 'F') {
                string i, x, y;
                cin >> i >> x >> y;
                cin.get();
                if (is.count(i)) {
                    flag = true;
                    break;
                } else {
                    is.insert(i);
                }
                loops.push(array<string, 3>({i, x, y}));
                rec.push_back(0);
                cnt++;
            } else {
                cnt--;
                if (cnt < 0) {
                    flag = true;
                    break;
                }
                auto a = loops.top();
                is.erase(loops.top()[0]);
                loops.pop();

                int add = genOC(a);
                if (-1 == add) {
                    rec.back() = 0;
                } else {
                    rec.back() += add;
                }
                auto tmp = rec.back();
                rec.pop_back();
                if (cnt == 0) {
                    // 栈清空了
                    oc = max(oc, tmp);
                } else {
                    rec.back() = max(rec.back(), tmp);
                }
            }
        }
        while (l > 0) {
            string s;
            std::getline(cin, s);
            flag = true;
            l--;
        }
        if (flag || cnt != 0) {
            cout << "ERR\n";
            continue;
        }
        if (oc == ns) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}