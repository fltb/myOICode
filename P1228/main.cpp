#include <iostream>
#include <cstdio>

using namespace std;
int XPrincess, YPrincess, XMap, YMap;

int Jurge (int x,int y,int zx,int zy,int l)
{
    if(x-zx<l&&y-zy<l)
    {
        return 0;
    }
    if(x-zx<l&&y-zy>=l)
    {
        return 1;
    }
    if(x-zx>=l&&y-zy<l)
    {
        return 2;
    }
    if(x-zx>=l&&y-zy>=l)
    {
        return 3;
    }
}

void dfs(int Xtag, int Ytag, int Xstart, int Ystart, int Len)
{
    if(Len <= 1) {  return;}
    Len>>=1;
    //0:left up, 1:right up, 2:left down, 3:right down
    int Control = Jurge(Xtag, Ytag, Xstart, Ystart,Len);
    switch(Control)
    {
    case 0:
        printf("%d %d 1\n", Xstart + Len, Ystart + Len);
        //
        dfs(Xtag, Ytag, Xstart, Ystart, Len);
        //
        dfs(Xstart + Len, Ystart + Len - 1, Xstart + Len, Ystart, Len);
        dfs(Xstart + Len - 1, Ystart + Len, Xstart, Ystart + Len, Len);
        dfs(Xstart + Len, Ystart + Len, Xstart + Len, Ystart + Len, Len);
        break;
    case 1:
        printf("%d %d 2\n", Xstart + Len, Ystart + Len - 1);
        //
        dfs(Xtag, Ytag, Xstart, Ystart + Len, Len);
        //
        dfs(Xstart + Len - 1, Ystart + Len - 1, Xstart, Ystart, Len);
        dfs(Xstart + Len - 1, Ystart + Len, Xstart, Ystart + Len, Len);
        dfs(Xstart + Len, Ystart + Len, Xstart + Len, Ystart + Len, Len);
        break;
    case 2:
        printf("%d %d 3\n", Xstart + Len - 1, Ystart + Len);
        //
        dfs(Xtag, Ytag, Xstart + Len, Ystart, Len);
        //
        dfs(Xstart + Len - 1, Ystart + Len - 1, Xstart, Ystart, Len);
        dfs(Xstart + Len, Ystart + Len - 1, Xstart + Len, Ystart,Len);
        dfs(Xstart + Len, Ystart + Len, Xstart + Len, Ystart + Len, Len);
        break;
    case 3:
        printf("%d %d 4\n", Xstart + Len - 1, Ystart + Len - 1);
        //
        dfs(Xtag, Ytag, Xstart + Len, Ystart + Len, Len);
        //
        dfs(Xstart + Len - 1, Ystart + Len - 1, Xstart, Ystart, Len);
        dfs(Xstart + Len, Ystart + Len - 1, Xstart + Len, Ystart, Len);
        dfs(Xstart + Len - 1, Ystart + Len, Xstart, Ystart + Len,Len);

        break;
    }
}

int main()
{
    int k, m, n;
    cin>>k>>m>>n;
    dfs(m,n,1,1,1<<k);
    return 0;
}
