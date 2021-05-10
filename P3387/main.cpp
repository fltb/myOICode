#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;
const int MAXN = 1000+2;

vector<int> Edge[MAXN];
int N, M, Val[MAXN];

///Tarjan begin::

int Dfn[MAXN], Low[MAXN], InStck[MAXN], Dag[MAXN], DagSum, Flag;
stack<int> Stck;
void tarjan(int u)
{
    
}


///Tarjan end::


int main()
{
    cin>>N>>M;
    for(int i = 1; i <= N; ++i)
    {
        scanf("%d",&Val[i]);
    }

    for(int i = 0; i <= M; ++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        Edge[u].push_back(v);
    }


    return 0;
}
