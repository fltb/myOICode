#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#define cosnt const;
using std::cin;
using std::cout;
using std::map;
using std::queue;
using std::set;
using std::string;

const int MAXD = 5;
struct Node {
    int dep;
    string str;
    Node(int dep_, string str_) : dep(dep_), str(str_) {}
    bool operator<(const Node& x) const {
        return str < x.str;
    }
    bool operator==(const Node& x) const {
        return str == x.str;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    string a, b;
    cin >> a >> b;

    string u, v;
    map<string, string> rule, deRule;
    while (cin >> u >> v) {
        rule[u] = v;
        deRule[v] = u;
    }

    auto replace = [](string s, string f, string t) {
        auto it = s.find(f);
        string ans = "";
        if (it) {
            ans += s.substr(0, it);
        }
        ans += t;
        if (s.length() > it + f.length()) {
            ans += s.substr(it + f.length());
        }
        return ans;
    };
    bool direct = true;  // 反着是 false
    set<Node> rec;
    int dep = 0, reDep = 0;
    queue<Node> que, reQue;

    auto bfs = [&rec, &dep, &que, &rule, &replace]() {
        while (!que.empty()) {
            const auto& st = que.front().str;
            const auto& de = que.front().dep;
            if (de > dep) {
                dep++;
                return true;
            }
            // 各个都走一遍
            for (auto& it : rule) {
                auto to = replace(st, it.first, it.second);
                rec.insert(Node(dep + 1, to));
                que.push(Node(dep + 1, to));
            }
        }
        return false;
    };

    auto reBfs = [&rec, &reDep, &reQue, &deRule, &replace]() {
        while (!reQue.empty()) {
            const auto& st = reQue.front().str;
            const auto& de = reQue.front().dep;
            if (de > reDep) {
                reDep++;
                return false;
            }
            // 各个都走一遍
            for (auto& it : deRule) {
                auto to = replace(st, it.first, it.second);
                for (int i = 0; i < MAXD + 1; i++) {
                    if (rec.count(Node(i, to))) {
                        cout << de + 1 + i << '\n';
                        return true;
                    }
                }
                reQue.push(Node(reDep + 1, to));
            }
        }
        return false;
    };

    que.push(Node(0, a));
    reQue.push(Node(0, b));
    while (true) {
        if (direct) {
            bfs();
        } else {
            if (reBfs()) {
                break;
            }
        }
        direct = !direct;
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