#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<cstring>
#define mian main
const int MODD = 80112002;

using namespace std;

vector<int> chi    [5000+3];
vector<int> beichi [5000+3];

int n,m;

int dfsreted [5000+3];
int dfs (int x)
{
    if(dfsreted[x] != 0)
        return dfsreted[x];
    if(chi[x].empty())//ShengChanZhe
    {
        dfsreted[x] = 1;
        return dfsreted[x];
    }
    int aaa = 0;
    for(vector<int>::iterator it = chi[x].begin(); it != chi[x].end(); it++)
    {
        aaa = (aaa+dfs(*it)) % MODD;
    }
    dfsreted[x] = aaa;
    return dfsreted[x];
}

int mian()
{
    ///
    ios::sync_with_stdio(false);
    ///
    while(cin>>n>>m){
    for (int i = 0; i < m; i++)
    {
        int a,b;
        //scanf("%d%d",&a,&b);
        cin>>a>>b;
        chi[b].push_back(a);
        beichi[a].push_back(b);
    }
    queue<int> xiaofeizhe;
    for(int i = 1;i <= n; i++)
    {
        if(beichi[i].empty())
            xiaofeizhe.push(i);
    }
    long long ans = 0;
    while(!xiaofeizhe.empty())
    {
        int xx = xiaofeizhe.front();
        xiaofeizhe.pop();

        ans = (ans+dfs(xx)) % MODD;
    }
    cout<<ans;
    for(int i = 0;i< 5003;i++)
        chi[i].clear();
    for(int i = 0;i< 5003;i++)
        beichi[i].clear();
    memset(dfsreted,0,sizeof(dfsreted));
    }
}
