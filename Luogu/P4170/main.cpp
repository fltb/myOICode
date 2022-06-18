#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
const int INF = 0x7fffffff;

int f[52][52],n;
string a;

int walk (int i, int j)
{
    if(a[i-1] == a[j-1])
    {
        //cout<<"walk "<<i<<" "<<j<<" "<<0<<endl;
        return 0;
    }
    else
    {
        //cout<<"walk "<<i<<" "<<j<<" "<<1<<endl;
        return 1;
    }
}

int dp(int i, int j)
{
    int & b = f[i][j];
    if(b != 0)
    {
        return b;
    }
    if(i == j)
    {
        return b = 1;
    }
    if(walk(i,j) == 0)
    {
        b = min(dp(i+1,j),dp(i,j-1));
    }
    else
    {
        int m = INF;
        for(int k = i; k < j; ++k)
        {
            m = min(m,dp(i,k)+dp(k+1,j));
        }
        b = m;
    }
    //cout << i << " " << j <<" "<<b<<endl;
    return b;
}

int main()
{
    cin>>a;
    n = a.size();
    dp(1,n);
    cout << f[1][n];
    return 0;
}
