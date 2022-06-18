#include <iostream>

using namespace std;

int relactives[5000 + 3];
int fnd_relc (int x);
int set_relc (int x,int y);
int main()
{
    int n,m,p;
    cin>>n>>m>>p;

    for(int i = 1; i <= n; i++)
    {
        relactives[i] = i;
    }
    for(int i = 1; i <= m; i++)
    {
        int m1,m2;
        cin>>m1>>m2;

        set_relc(m1,m2);
    }

    for(int i = 1; i <= p; i++)
    {
        int p1,p2;
        cin>>p1>>p2;
        if(fnd_relc(p1) == fnd_relc(p2))
            cout<<"Yes"<<endl;
        else
            cout<<"No" <<endl;
    }
    return 0;
}
int fnd_relc(int x)
{
    if( x != relactives [x] )
        relactives [x] = fnd_relc (relactives [x]);
    return relactives [x];
}
int set_relc (int x, int y)
{
    int f1 = fnd_relc(x);
    int f2 = fnd_relc(y);
    relactives[f1] = f2;
    return 0;
}
