#include <iostream>
#include <vector>
using std::cin;
using std::cout;
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
const int MAXN = 100000 + 5;
int dfn[MAXN], low[MAXN], cnt;
bool cut[MAXN];
std::vector<int> graph[MAXN];
void tarjan(int x, int fa) {
    int childs = 0;
    dfn[x] = low[x] = ++cnt;
    for (auto to : graph[x]) {
        if (!dfn[to]) {
            ++childs;
            tarjan(to, x);
            low[x] = min(low[x], low[to]);
            cut[x] = cut[x] || !(fa == x) && dfn[x] <= low[to];
        } else if (fa != to) {
            low[x] = min(low[x], dfn[to]);
        }
    }
    cut[x] = cut[x] || (fa == x && childs >= 2);
}
int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, i);
        }
    }
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        tot += cut[i];
    }
    cout << tot << '\n';
    for (int i = 1; i <= n; i++) {
        if (cut[i]) {
            cout << i << ' ';
        }
    }
    cout << '\n';
    return 0;
}