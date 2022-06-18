#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::scanf;
using std::printf;

const int MAXN = 5000+2, MAXM = 200000 + 2;

int fa[MAXN]; //并查集用的

struct Edge
{
    int from, to, val;

    bool operator<(const Edge & x) const
    {
        return val < x.val;
    }
};
std::vector<Edge> Graph;

int find_fa(int x)
{
    if(x == fa[x])
    {
        return x;
    }
    else
    {
        return fa[x] = find_fa(fa[x]);
    }
}

int merge_fa(int x, int y)
{
    fa[find_fa(x)] = find_fa(y);
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int from, to, val;
        scanf("%d%d%d", &from, &to, &val);
        Edge t;
        t.from = from;
        t.to = to;
        t.val = val;
        Graph.push_back(t);
    }

    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
    }

    std::sort(Graph.begin(), Graph.end());
    int ans = 0, count = 0;
    //cout << endl;
    for (std::vector<Edge>::iterator it = Graph.begin(); it != Graph.end(); ++it)
    {
        //cout << it->from << " " << it->to <<" "<< it->val << endl;
        if (find_fa(it->from) == find_fa(it->to))
        {
            continue;
        }
        //cout << it->from << " " << it->to << " " << it->val << "entered" << endl;

        merge_fa(it->from, it->to);
        ans += it->val;
        ++count;
        if (n - 1 == count)
        {
            break;
        }
    }
    if (n - 1 == count)
        cout << ans << endl;
    else
        cout << "orz\n";

    return 0;
}
