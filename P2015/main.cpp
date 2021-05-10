#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
const int INF = 0x7fffffff, MAXN = 200 + 2;

int N,Q;
int v[MAXN][MAXN],  f[MAXN][MAXN], idx[MAXN];
vector<int> s[MAXN];
void dfs(int b)
{
    idx[b] = 1;
    for(int i = 0; i < s[b].size(); ++i)
    {
        int c = s[b][i];
        if(!idx[c])
        {
            idx[c] = 1;
            dfs(c);
            for(int j = Q; j >= 1; --j)
            {
                for(int k = j-1; k >= 0; --k)
                {
                    f[b][j] = max(f[b][j], f[b][j-k-1] + f[c][k] + v[b][c]);
                }
            }
        }
    }
}


int main()
{
    cin>>N>>Q;
    for(int i = 1; i < N; ++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        v[a][b] = v[b][a] = c;
        s[a].push_back(b); s[b].push_back(a);
    }
    dfs(1);
    cout<<f[1][Q];
    return 0;
}
