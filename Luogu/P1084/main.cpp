#include <algorithm>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#define cosnt const;
using std::cin;
using std::cout;
using std::function;
using std::multiset;
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
const int MAXN = 50000 + 2, MAX_DEP = 16;
long long INF = 0x3f3f3f3f3f3f3f3f;
struct Edge {
    int u, v, c;
    Edge(int u_, int v_, int c_) : u(u_), v(v_), c(c_) {}
    int to(int x) { return x == u ? v : u; }
};
struct Army {
    int at;
    long long len;
    Army(int a, long long l) : at(a), len(l) {}
    bool operator<(const Army& x) const {
        return len == x.len ? at < x.at
                            : len < x.len;
    }
};
vector<Edge> edges;
vector<vector<int>> graph;
multiset<Army> armys;
int n;
namespace check {
int fa[MAXN][MAX_DEP];  // 2's powers
long long faSum[MAXN][MAX_DEP];
long long limit;
void dfsFa(int x, int f, int fae) {  // generate fa and faSum.
#ifdef FLOATINGBLOCKS
    cout << "At " << x << '\n';
#endif
    fa[x][0] = f;
    faSum[x][0] = fae != -1 ? edges[fae].c : 0;
    for (int jump = 1; jump < MAX_DEP; jump++) {
        fa[x][jump] = fa[max(f, 0)][jump - 1];
        faSum[x][jump] = faSum[max(f, 0)][jump - 1] + faSum[x][0];
#ifdef FLOATINGBLOCKS
        cout << "    j=" << jump << " " << fa[x][jump] << " " << faSum[x][jump] << std::endl;
#endif
    }
    for (auto ei : graph[x]) {
        auto to = edges[ei].to(x);
        if (to != f) {
            dfsFa(to, x, ei);
        }
    }
}
void init() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAX_DEP; j++) {
            fa[i][j] = -1;
            faSum[i][j] = 0;
        }
    }
    dfsFa(1, -1, -1);
}
// 编号
int hasArmy[MAXN];
struct cmp {
    bool operator()(const Army& a, const Army& b) const {
        return a.at == b.at ? a.len < b.len : a.at < b.at;
    }
};
multiset<Army> subTreeArmyLengthed;
multiset<Army, cmp> subTreeArmyIndexed;
void walk() {
#ifdef FLOATINGBLOCKS
    cout << "Recored\n";
#endif
    for (auto army : armys) {
        // 进行往上跳的测试，如果有父亲就看看长度，-1 说明可以到根
        auto at = army.at;
        int j = MAX_DEP - 1;
        long long total = 0;
        while (j >= 0) {
            if (fa[at][j] != -1 && total + faSum[at][j] <= limit) {
                if (fa[at][j] == 1) {
                    j--;
                    while (j >= 0) {
                        if (fa[at][j] == 1 || fa[at][j] == -1) {
                            j--;
                        } else {
                            at = fa[at][j];
                        }
                    }
                    total = faSum[army.at][MAX_DEP - 1];
                    subTreeArmyIndexed.insert(Army(at, total));
                    subTreeArmyLengthed.insert(Army(at, total));
#ifdef FLOATINGBLOCKS
                    cout << "    Subtree " << at << " len " << total << std::endl;
#endif
                    break;
                }
                at = fa[at][j];
                total += faSum[at][j];
            } else {
                j -= 1;
            }
        }
        hasArmy[at]++;
    }
}
// 处理完成之后进入下一步，就是判断是否能够到达叶子
bool toLeaf(int x, int fa) {
    bool hasLeaf = false, leaf = true;
    for (auto eid : graph[x]) {
        auto to = edges[eid].to(x);
        if (to != fa) {
            leaf = false;
            if (hasArmy[to]) {
                continue;
            }
            hasLeaf = hasLeaf || toLeaf(to, x);
        }
    }
    return hasLeaf || leaf;
}
// 对于那些可以到达根节点的节点当中多余的那些，调到其他子树上面
bool tackleLeaf() {
    for (auto eid : graph[1]) {
        auto sub = edges[eid].to(1);
        if (toLeaf(sub, -1)) {
            if (hasArmy[sub]) {
                auto it = subTreeArmyIndexed.lower_bound(Army(sub, INF));
                if (it != subTreeArmyIndexed.begin()) {
                    --it;
                    if (it->at == sub) {
                        auto army = *it;
                        subTreeArmyIndexed.erase(it);
                        subTreeArmyLengthed.erase(subTreeArmyLengthed.lower_bound(army));  // 免得删多了
                        hasArmy[sub]--;
                    } else {
                        return false;
                    }
                }
            } else {  // 要调兵了
                auto it = subTreeArmyLengthed.lower_bound(Army(MAXN, limit - edges[eid].c));
                if (it != subTreeArmyLengthed.begin()) {
                    --it;
                    auto army = *it;
                    subTreeArmyLengthed.erase(it);
                    subTreeArmyIndexed.erase(subTreeArmyIndexed.lower_bound(army));
                    hasArmy[sub]--;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}
bool check() {
    for (int i = 0; i <= n; i++) {
        hasArmy[i] = 0;
    }
    subTreeArmyIndexed.clear();
    subTreeArmyLengthed.clear();
    walk();
    return tackleLeaf();
}
}  // namespace check
int main() {
    std::ios::sync_with_stdio(false);
    cin >> n;
    graph = vector<vector<int>>(n + 1, vector<int>());
    long long l = 0, r = 0;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        r += c;
        edges.push_back(Edge(u, v, c));
        graph[u].push_back(edges.size() - 1);
        graph[v].push_back(edges.size() - 1);
    }
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int a;
        cin >> a;
        armys.insert(Army(a, 0));
    }
    check::init();
    int ans = -1;
    while (l <= r) {
        check::limit = (l + r) / 2;
        if (check::check()) {
            ans = check::limit;
            r = check::limit - 1;
        } else {
            l = check::limit + 1;
        }
    }
    cout << ans << '\n';
    return 0;
}