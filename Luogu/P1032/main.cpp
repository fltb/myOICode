#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::queue;
using std::set;
using std::string;

const int MAXD = 5;
struct Node {
    int dep;
    string str;
    Node(int dep_, string str_) : dep(dep_), str(str_) {}
    bool operator<(const Node& x) const {
        return (str == x.str) ? dep < x.dep : str < x.str;
    }
    bool operator==(const Node& x) const {
        return str == x.str && dep == x.dep;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    string a, b;

    cin >> a >> b;

    string u, v;
    std::vector<std::pair<string, string>> rule, deRule;
    while (cin >> u >> v) {
        rule.push_back(std::make_pair(u, v));
        deRule.push_back(std::make_pair(v, u));
    }

    bool direct = true;  // 反着是 false
    set<string> vis;
    set<Node> rec;
    int dep = 0, reDep = 0;
    queue<Node> que, reQue;
    auto bfs = [&que, &rule, &vis, &b]() {
        while (!que.empty()) {
            const auto& st = que.front().str;
            const auto& de = que.front().dep;
            que.pop();
            /*if (de > dep) {
                dep++;
                return true;
            }*/
            if (st == b) {
                return de;
            }
            if (de > 10) {
                return de;
            }
            // 各个都走一遍
            for (auto& it : rule) {
                auto i = st.find(it.first);
                while (i != string::npos) {
                    string ans = "";
                    if (i) {
                        ans += st.substr(0, i);
                    }
                    ans += it.second;
                    if (st.length() > i + it.first.length()) {
                        ans += st.substr(i + it.first.length());
                    }
                    #ifdef FLOATINGBLOCKS
                    cout << ans << std::endl;
                    #endif
                    if (vis.count(ans) != 1) {
                        vis.insert(ans);
                        // rec.insert(Node(de + 1, ans));
                        que.push(Node(de + 1, ans));
                    }
                    i = st.find(it.first, i + 1);  // Find the next occurrence
                }
            }
        }
        return 100;
    };

    /*auto reBfs = [&rec, &reDep, &reQue, &deRule, &vis]() {
        while (!reQue.empty()) {
            const auto& st = reQue.front().str;
            const auto& de = reQue.front().dep;
            reQue.pop();
            if (de > reDep) {
                reDep++;
                return false;
            }
            for (auto& it : deRule) {
                auto i = st.find(it.first);
                while (i != string::npos) {
                    string ans = "";
                    if (i) {
                        ans += st.substr(0, i);
                    }
                    ans += it.second;
                    if (st.length() > i + it.first.length()) {
                        ans += st.substr(i + it.first.length());
                    }
                    if (vis.count(ans)) {
                        for (int j = 0; j < MAXD + 1; j++) {
                            if (rec.count(Node(j, ans)) && *rec.find(Node(j, ans)) == Node(j, ans)) {
                                cout << de + 1 + j << '\n';
                                return true;
                            }
                        }
                    }
                    reQue.push(Node(de + 1, ans));
                    i = st.find(it.first, i + 1);  // Find the next occurrence
                }
            }
        }
        return false;
    };*/

    que.push(Node(0, a));
    // reQue.push(Node(0, b));
    auto re = bfs();
    if (re == 0 || re > 10) {
        cout << "NO ANSWER!\n";

    } else {
        cout << re << '\n';
    }

    return 0;
}

/*
尝试一个实现
记录下每次搜索出来的字符串，正着的一个 set 记下来，每层分开记下
正方向搜完一层之后，开始进行反方向的搜索。
反方向每次搜索一个之后就看看正方向是不是有了对应的，如果有那就当作它是答案了。
如果反方向搜了一层还没有搜完就回到正方向。
*/