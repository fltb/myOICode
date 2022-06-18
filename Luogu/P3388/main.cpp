#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using std::cin;
using std::cout;
using std::vector;
int min(int a, int b) {
    return a < b ? a : b;
}
const int MAXN = 100000 + 5;

vector<int> graph[MAXN];
int n, m;
int dfn[MAXN], cnt, low[MAXN], cuts[MAXN], fa[MAXN], total;
void tarjan(int now) {
    dfn[now] = low[now] = ++cnt;
    for (auto it = graph[now].begin(); it != graph[now].end(); it++) {
        int to = *it;
        if (!dfn[to]) {
            fa[to] = now;
            tarjan(to);
            low[now] = min(low[to], low[now]);
            if (low[to] >= dfn[now]) {
                cuts[now] = 1;
            }
        } else if (fa[now] != to) {
            low[now] = min(low[now], dfn[to]);
        }
    }
}

void tarjanRoot(int root) {
    fa[root] = -1;
    dfn[root] = low[root] = ++cnt;
    int kids = 0;
    for (auto it = graph[root].begin(); it != graph[root].end(); it++) {
        int to = *it;
        if (!dfn[to]) {
            fa[to] = root;
            tarjan(to);
            kids++;
        }
    }
    if (kids >= 2) {
        cuts[root] = 1;
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjanRoot(i);
        }
    }
    total = 0;
    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (cuts[i]) {
            total++;
            q.push(i);
        }
    }
    cout << total << "\n";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n";
    return 0;
}