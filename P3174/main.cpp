#include <iostream>
#include <cmath>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

const int MAXN = 300000 + 2;

vector<int> graph[MAXN];
int n, rec[MAXN], ans;

void dfs(int x, int fa)
{
    int & rt = rec[x];
    int mx1 = 0, mx2 = 0; // max
    for (size_t i = 0; i < graph[x].size(); ++i)
    {
        int next = graph[x][i];
        if (next != fa)
        {
            dfs(next, x);
            int rts = rec[next];
            rt = max(rt, rts);
            if (rts > mx1)
            {
                mx2 = mx1;
                mx1 = rts;
            } 
            else if (rts > mx2)
            {
                mx2 = rts;
            }
        }
    }
    // 只有这三行复制题解，然后过了？？？
	int cnt=graph[x].size() - (fa!=-1);
	rec[x] += (1 + max(0, cnt - 1));
	ans=max(ans, mx2 + mx1 + 1 + max(0, cnt - 1 - (fa == -1)));
}

int main()
{
    int m;
    cin >> n >> m;
    if (n == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1, -1);
    cout << ans << endl;
    return 0;
}
