/*
LCA

每次，
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::scanf;
using std::printf;

const int MAXN = 500000 + 1;

int fa[MAXN][20], // remote father, fa[point][num]
    deep[MAXN],
    n, m, s;
std::vector<int> Edge[MAXN];

void dfs(int now, int father)
{
  deep[now] = deep[father] + 1;
  fa[now][0] = father;
  for (int i = 1; deep[now] > (1<<i); ++i)
  {
    fa[now][i] = fa[fa[now][i-1]][i-1];
  }
  for (int i = 0; i < Edge[now].size(); ++i)
  {
    int v = Edge[now][i];

    if (v != father)
    {
      dfs(v, now);
    }
  }
}

int LCA(int a, int b)
{
  int da = deep[a],
      db = deep[b];

  if (da != db) // make their deep equal
  {
    if (da < db)
    {
      std::swap(da, db);
      std::swap(a, b);
    }
    int tmpd = da - db;
    int lg2d = log(tmpd)/log(2) + 0.5;
    for (int i = 0; i <= lg2d; ++i)
    {
      if (tmpd & (1<<i))
      {
        a = fa[a][i];
      }
    }
  }

  if (a == b)
  {
    return a;
  }

  for (int i = 19; i >= 0; --i)
  {
    if( deep[ fa[a][i] ] <= 0 || fa[a][i] == fa[b][i] )
    {
      continue;
    }
    else
    {
      a = fa[a][i];
      b = fa[b][i];
    }
  }

  return fa[a][0];

}

int main()
{
  cin >> n >> m >> s;
  for (int i = 1; i < n; ++i)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    Edge[u].push_back(v);
    Edge[v].push_back(u);
  }
  deep[s] = 1;
  for (int i = 0; i < Edge[s].size(); ++i)
  {
    dfs(Edge[s][i], s);
  }

  for (int i = 0; i < m; ++i)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%d\n", LCA(u, v) );
  }

  return 0;
}
