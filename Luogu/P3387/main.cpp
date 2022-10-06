#include <iostream>
#include <stack>
#include <vector>
using std::cin;
using std::cout;
using std::stack;
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
template <typename T>
inline T max(T a, T b) {
    return a > b ? a : b;
}
const int MAXN = 100000 + 5;
int dfn[MAXN], low[MAXN], cnt;
bool ins[MAXN];
stack<int> st;
std::vector<int> graph[MAXN];
std::vector<std::vector<int>> newg;
int gtoNg[MAXN];
int val[MAXN];
void tarjan(int x) {
    st.push(x);
    ins[x] = dfn[x] = low[x] = ++cnt;
    for (auto to : graph[x]) {
        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (ins[to]) {
            low[x] = min(low[x], dfn[to]);
        }
    }
    if (dfn[x] == low[x]) {
        newg.push_back(std::vector<int>());
        auto rec = 0;
        do {
            rec = st.top();
            st.pop();
            ins[rec] = 0;
            newg.back().push_back(rec);
            gtoNg[rec] = newg.size() - 1;
        } while (rec != x);
    }
}
int dp[MAXN], vis[MAXN];
int dponT(int c) {
    int& vv = dp[c];
    if (vv) {
        return vv;
    }
    vis[c] = 1;
    int sum = 0;
    for (auto ct : newg[c]) {
        for (auto to : graph[ct]) {
            int cc = gtoNg[to];
            if (!vis[cc]) {
                dponT(cc);
            }
            vv = max(vv, dp[cc]);
        }
        sum = max(sum, sum + val[ct]);
    }
    vv += sum;
    return vv;
}
int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[gtoNg[i]]) {
            ans = max(ans, dponT(gtoNg[i]));
        }
    }
    cout << ans << '\n';
    return 0;
}