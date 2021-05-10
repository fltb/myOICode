#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int MAXN = 2000 + 3;

int DfsReturned[MAXN][MAXN];
char StrA[MAXN], StrB[MAXN];

int dfs (int CurA,int CurB)
{
    if(CurA == -1)
    {
        //cout<<"StrA: "<<StrA[CurA]<<" StrB: "<<StrB[CurB]<<endl;
        return CurB + 1;
    }
    if(CurB == -1)
    {
        return CurA + 1;
    }

    if(DfsReturned[CurA][CurB] != -1)
    {
        return DfsReturned[CurA][CurB];
    }

    if(StrA[CurA] == StrB[CurB])
    {
        return DfsReturned[CurA][CurB] = dfs(CurA - 1, CurB - 1);
    }
    else
    {
        return DfsReturned[CurA][CurB] = min( min( dfs(CurA - 1, CurB), dfs(CurA, CurB - 1) ), dfs(CurA - 1,CurB - 1) ) + 1;
    }
}

int main()
{
    cin>>StrA>>StrB;

    int LenA = strlen(StrA);
    int LenB = strlen(StrB);

    memset(DfsReturned,-1,sizeof(DfsReturned));

    cout << dfs(LenA - 1, LenB - 1);
    return 0;
}
