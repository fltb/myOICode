#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
const int maxn = 10000 + 3;

int ans[maxn],tIme[maxn];
bool vised[maxn];
vector<int> edge[maxn];
vector<int> topo;
int n;

void dfs (int u,int len)
{
    if(vised[u]) return;
    for(int i = 0; i < edge[u].size() ; i++)
    {
        const int & v = edge[u][i];
        if(!vised[v])
            dfs(v,len+tIme[v]);
    }
    topo.push_back(u);
    vised[u] = true;
    ans[u] = len+tIme[u];
}
void toposort ()
{
    for(int u = 0; u < n;++u)
    {
        dfs(u,tIme[u]);
    }
    reverse(topo.begin(),topo.end());
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i = 0; i < n; ++i)
    {
        int now,len,ed;
        cin>>now>>len>>ed;
        tIme[now] = len;
        while(ed != 0)
        {
            edge[ed].push_back(now);
            cin>>ed;
        }
    }
    toposort();
    int FinalAns = 0;
    for(int i = 1; i<=n; ++i)
    {
        FinalAns = max(FinalAns,ans[i]);
    }
    cout<<FinalAns;
    return 0;
}

/*struct NodeOfGraph
{
    vector<int> NextAdjVex,
                 FatherAdjVex;
    bool HaveFather;
    int len,
        StartTime,
        CurNext,
        CurFather;
    NodeOfGraph(){HaveFather = false;CurFather = 0;CurNext = 0;}
    bool operator<(const NodeOfGraph & ano_node){return len < ano_node.len;}
}graph[maxn];

int n;
int Pushed[maxn];

int main()
{
    ios::sync_with_stdio(false);

    cin>>n;
    for(int i = 1; i <= n; ++i)
    {
        int now,len,each;
        cin>>now>>len>>each;
        graph[now].len = len;
        while(each != 0)
        {
            graph[now].FatherAdjVex.push_back(each);
            graph[each].NextAdjVex.push_back(now);
            graph[now].HaveFather = true;
            ++graph[each].CurNext;
            cin>>each;
        }
    }
    //Toposort
    queue<int> TopoSortQueue;
    for(int i = 1; i <= n; ++i)
    {
        if(graph[i].HaveFather == false)
        {
            graph[i].StartTime = 0;
            TopoSortQueue.push(i);
            cout<<"k= "<<i<<endl;
        }
    }
    while(!TopoSortQueue.empty())
    {
        int TmpGraphCur = TopoSortQueue.front();TopoSortQueue.pop();
        NodeOfGraph & TmpGraph = graph[TmpGraphCur];
        cout<<TmpGraphCur<<" now:"<<endl;
        int & i = TmpGraph.CurNext;
        for( ;TmpGraph.CurNext >=0; --TmpGraph.CurNext)
        {
            graph[ TmpGraph.NextAdjVex[i] ].StartTime = TmpGraph.len + TmpGraph.StartTime;
            TopoSortQueue.push( TmpGraph.NextAdjVex[i] );
            cout<<TmpGraph.NextAdjVex[i]<<endl;
        }

    }
    return 0;
}
*/
