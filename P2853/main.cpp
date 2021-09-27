#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
const int KMAX = 100 + 2, NMAX = 1000 + 2, MMAX = 10000 + 2;

struct EachFarm
{
    int Cows;
    //int VisSum;
    map <int,int> MpVised;
    vector<int> NexFarm;
    EachFarm() {Cows = 0;}
}Farm[NMAX];

int k, n, m, HaveCowsFarmNum = 0;

void dfs (int x, int num)
{
    if(Farm[x].MpVised[num] != 0)
        return;
    Farm[x].MpVised[num] = 1;
    //cout<<"    Farm["<<x<<"], num set as "<<num<<endl;
    //Farm[x].VisSum++;
    for(int i = 0;i < Farm[x].NexFarm.size(); ++i)
    {
        const int v = Farm[x].NexFarm[i];
        if(x != v && Farm[v].MpVised[num] == 0)
        {
            dfs(v,num);
        }
    }
}
int main()
{
    freopen("P2853_5.in","r",stdin);
    //freopen("out.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin>>k>>n>>m;
    for(int i = 1; i <= k ; ++i)
    {
        int tmp;
        cin>>tmp;
        Farm[tmp].Cows = i;
        ++HaveCowsFarmNum;
    }
    for(int i = 1;i <= m ; ++i)
    {
        int u,v;
        cin>>u>>v;
        if(u != v)
            Farm[u].NexFarm.push_back(v);
    }
    int sum = HaveCowsFarmNum;
    for(int i = 1; i <= n; ++i)
    {
        if(Farm[i].Cows != 0)
        {

            //cout<<"i =  "<<i<<"sum = "<<sum<<endl;
            dfs(i,sum);
            sum--;

        }
    }
    int ans = 0;
    for(int i = 1; i <= n; ++i)
    {
        bool OK = true;
        for(int j = HaveCowsFarmNum; j > sum; --j)
        {
            if(Farm[i].MpVised[j] != 1)
            {
                OK = false;
                //cout<<i<<" at j = "<<j<<"failed"<<endl;
                break;
            }
        }
        if(OK)
        {
            ans++;
            //cout<<"at:"<<i<<endl;
        }
    }
    cout<<ans;
    return 0;
}
