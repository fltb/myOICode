#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int MAXK = 10000 + 3;
struct EEdge
{
    int start,
        len;
    EEdge(){start = 0; len = 0;}
    bool operator<(const EEdge & x) const
    {
        if(start > x.start )
        {
            return true;
        }
        return false;
    }
}Edge [MAXK];

int N,K,Answer[MAXK],Sum[MAXK];

int main()
{
    ios::sync_with_stdio(false);
    cin >> N >> K;
    for(int i = 1; i <= K; ++i)
    {
        int TmpP,TmpT;
        cin >> TmpP >> TmpT;
        Edge[i].start = TmpP;
        Edge[i].len   = TmpT;
        ++Sum[TmpP];
    }
    sort(Edge + 1,Edge + K + 1);
    int Cur = 1;
    //for(int i = N - 1; i >= 0; --i)
    for(int i = N    ; i >= 1; --i)
    {
        if(!Sum[i])
        {
            Answer[i] = Answer[i + 1] + 1;
            /*if(i == 11)
            {
                cout<<"WWWWWWWWWWWWWWWWWWW\n";
            }*/
        }
        else
        {
            for(int j = 0; j < Sum[i]; ++j)
            {

                if(i != Edge[Cur].start)
                {
                    cout<<"\nERROR: i = "<<i<<" Edge[Cur].start = "<<Edge[Cur].start<<" Cur = "<<Cur<<"\n";
                }
                if(Answer[i] < Answer[i + Edge[Cur].len])
                {
                    Answer[i] = Answer[i + Edge[Cur].len];
                }
                ++Cur;
            }
        }
    }
    cout<<Answer[1];
    return 0;
}
