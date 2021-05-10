#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
long long w [10000002];
long long v [10000002];
long long ans[10000002];
int main()
{
    long long time, m;
    cin>>time>>m;

    for(long long i = 0; i < m; i++)
    {
        cin>>w[i]>>v[i];
    }
    for(int i = 0; i < m ; i++)
    {
        for(int j = w[i];j <= time;j++)
        {
            ans[j] = max(ans[j], ans[j - w[i]] +  v[i]);
        }
    }
    cout<<ans[time];

    return 0;
}
